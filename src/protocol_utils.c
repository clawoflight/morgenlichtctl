#include "protocol_utils.h"

#define SOH "\001" ///< Start of Heading
#define STX "\002" ///< Start of text
#define ETX "\003" ///< End of text
#define EOT "\004" ///< End of transmission
#define ACK "\006" ///< Acknowledgment
#define NAK "\025" ///< Negative acknowledgment
#define BEL "\007" ///< Bell
#define RS  "\036" ///< Record separator
#define US  "\037" ///< Unit separator
#define REQ_HELLO "hello" ///< The server information request
#define REQ_ALRM_ADD "alarm-add" ///< The alarm addition request
#define REQ_ALRM_ENA "alarm-enable" ///< The alarm enable request
#define REQ_ALRM_DIS "alarm-disable" ///< The alarm disable request
#define REQ_ALRM_DEL "alarm-delete" ///< The alarm deletion request
#define REQ_ALRM_LS "alarm-list" ///< The alarm list request

#define PROTOCOL_VERSION "0.3"

int parse_response(char* status, char** payload)
{
    /* Read the response into the buffer */
    char buf[500];
    for (int i = 0; i < 500; ++i)
    {
        char c = network_read_char();
        if (c == -1) {
            term_networking();
            return 1;
        }

        buf[i] = c;
        if (c == '\0') // Stop reading at ASCII NULL
            break;
    }

// If DEBUG_TCP is set, print out the entire response
#ifdef DEBUG_TCP
    /* print the received message body */
    printf("\x1b[36;1m"); // ANSI bright cyan code
    printf("Received TCP message: ");
    for (int i = 0; i < strlen(buf); ++i)
    {
        /* Non-printing characters are replaced by their escape representation */
        if (isprint(buf[i]))
            printf("%c", buf[i]);
        else
            printf("\\%03o", buf[i]);
    }
    printf("\x1b[0m\n"); // reset ANSI escapes
#endif //DEBUG_TCP

    char ack_nack = EOF;
    char msg[50];
    // Scan the beginning of the response and check if it contains a message.
    if (sscanf(buf, "%c"BEL"%49[0-9a-zA-z _-]s"ETX, &ack_nack, msg) == 2)
        printf("Message from the server: %s\n", msg);

    // Write the status code to the receiving variable
    *status = ack_nack;

    // Locate STX to find the beginning of the payload
    char* payload_start = strchr(buf, *STX);

    /* If no payload was found */
    if (payload_start == NULL) {
        *payload = NULL;
        return 0;
    }

    /* Copy the payload to dynamic memory */
    *payload = malloc(strlen(payload_start) + 1);
    if (payload == NULL) {
        fprintf(stderr, "Could not allocate memory for the payload.\n");
        return 1;
    }
    strcpy(*payload, payload_start);

    return 0;
}

int server_info(const char *const hostname)
{
    if (init_networking(hostname))
        return 1;

    char msg[50];
    /* Prepare the request */
    snprintf(msg, 50, SOH"%s"US""REQ_HELLO""ETX""EOT, PROTOCOL_VERSION);

    /* Send the request */
    if (network_write(msg)) {
        term_networking();
        return 1;
    }

    /* Parse the response */
    char ack_nack;
    char* payload;
    if (parse_response(&ack_nack, &payload)) {
        term_networking();
        return 1;
    }

    int return_value = 0;
    // NAK
    if (ack_nack == *NAK) {
        fprintf(stderr, "The server could not fulfill the request.\n");
        return_value = 1;

    // ACK
    } else if (ack_nack == *ACK) {
        char hostname[50];
        char version[50];
        int protocol_major;
        int protocol_minor;

        // No payload
        if (payload == NULL) {
            fprintf(stderr, "Illegal response: no payload.\n");
            return_value = 1;
        }

        // Parse the payload and handle invalid content
        if (sscanf(payload, STX"%49[0-9a-zA-Z._- ]"US"%49[0-9a-zA-Z._-]"US"%d.%d"ETX""EOT,
            hostname, version, &protocol_major, &protocol_minor) != 4) {
            fprintf(stderr, "Illegal response: invalid payload.\n");

            return_value = 1;

        // Correct payload
        } else {
            printf("The server is running morgenlichtd %s (protocol %d.%d) on %s.\n",
                version, protocol_major, protocol_minor, hostname);
        }


    // Neither ACK nor NACK
    } else {
        fprintf(stderr, "Illegal response: missing status code.\n");
        return_value = 1;
    }

    free(payload); // NOTE: Never forget this!
    term_networking();
    return return_value;
}

int alarm_basic_cmd(const char *const hostname, const char *const profile, enum AlarmCmd cmd)
{
    if (init_networking(hostname))
        return 1;

    // Determine the command
    char* protocol_cmd = "";
    switch(cmd) {
        case AlarmEnable:
            protocol_cmd = REQ_ALRM_ENA;
            break;
        case AlarmDisable:
            protocol_cmd = REQ_ALRM_DIS;
            break;
        case AlarmDelete:
            protocol_cmd = REQ_ALRM_DEL;
            break;
    }

    char msg[200];
    /* Prepare the request */
    snprintf(msg, 200, SOH"%s"US"%s"ETX""STX"%s"ETX""EOT, PROTOCOL_VERSION, protocol_cmd, profile);

    /* Send the request */
    if (network_write(msg)) {
        term_networking();
        return 1;
    }

    /* Parse the response */
    char ack_nack;
    char* payload;
    if (parse_response(&ack_nack, &payload)) {
        term_networking();
        return 1;
    }

    int return_value = 1;
    // NAK
    if (ack_nack == *NAK) {
        fprintf(stderr, "The server could not fulfill the request.\n");
    } else if (ack_nack == *ACK) {
        puts("Operation completed successfully.");
        return_value = 0;
    } else {
        fprintf(stderr, "Illegal response: missing status code.\n");
    }


    if (payload != NULL)
        free(payload);
    term_networking();
    return return_value;
}
