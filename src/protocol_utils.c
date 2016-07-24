/* © 2015, 2016 Andreas Postel and Bennett Piater.
 This file is part of morgenlichtctl.

 Morgenlichtctl is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, version 3 of the License.
 morgenlichtctl is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with morgenlichtctl. If not, see <http://www.gnu.org/licenses/>.
*/
#include "protocol_utils.h"

#define PROTOCOL_VERSION "0.1"

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
    if (sscanf(buf, "%c\007%49[0-9a-zA-z ]s\003", &ack_nack, msg) == 2)
        printf("Message from the server: %s\n", msg);

    // Write the status code to the receiving variable
    *status = ack_nack;

    // Locate STX to find the beginning of the payload
    char* payload_start = strchr(buf, '\002');

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
    snprintf(msg, 50, "\001%s\037hello\003\004", PROTOCOL_VERSION);

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
    if (ack_nack == '\025') {
        fprintf(stderr, "The server could not fulfill the request.\n");
        return_value = 1;

    // ACK
    } else if (ack_nack == '\006') {
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
        if (sscanf(payload, "\002%49[0-9a-zA-Z ]\037%49[0-9a-zA-Z._-]\037%d.%d\003\004",
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
