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
#include "various.h"

#define PROTOCOL_VERSION "0.1"

int server_info(const char *const hostname)
{
    /// @todo: extract an extraction layer from this function
    // It could read the response, parse it into a header and body, and extract the status code.

    if (init_networking(hostname))
        return 1;

    char msg[50];
    // Prepare the request
    snprintf(msg, 50, "\001%s\037hello\003\004", PROTOCOL_VERSION);

    // Send the request
    if (network_write(msg)) {
        term_networking();
        return 1;
    }

    // Read the request into the buffer
    char buf[500];
    for (int i = 0; i < 500; ++i)
    {
        char c = network_read_char();
        if (c == -1) {
            term_networking();
            return 1;
        }

        buf[i] = c;
        if (c == '\0')
            break;
    }

    char ack_nack = EOF;
    // Scan the beginning of the response and check if it contains a message.
    if (sscanf(buf, "%c\007%49[0-9a-zA-z ]s\003", &ack_nack, msg) == 2)
        printf("Message from the server: %s\n", msg);


    int status = 0;
    // NAK
    if (ack_nack == '\025') {
        printf("The server could not fulfill the request.\n");
        status = 1;

    // ACK
    } else if (ack_nack == '\006') {
        char hostname[50];
        char version[50];
        int protocol_major;
        int protocol_minor;

        // Find STX to locate the beginning of the payload
        char* payload = strchr(buf, '\002');

        // No payload
        if (payload == NULL) {
            printf("Illegal response: no payload.\n");
            status = 1;
        }

        // Parse the payload and handle invalid content
        if (sscanf(payload, "\002%49[0-9a-zA-Z ]\037%49[0-9a-zA-Z._-]\037%d.%d\003\004",
            hostname, version, &protocol_major, &protocol_minor) != 4) {
            printf("Illegal response: invalid payload.\n");

            // debugging output
            // for (int i = 0; i < strlen(payload); ++i)
            // {
            //     if (isprint(payload[i]))
            //         printf("%c", payload[i]);
            //     else
            //         printf("\%o", payload[i]);
            // }

            status = 1;

        // Correct payload
        } else {
            printf("The server is running morgenlichtd %s (protocol %d.%d) on %s.\n",
                version, protocol_major, protocol_minor, hostname);
        }


    // Neither ACK nor NACK
    } else {
        printf("Illegal response: missing status code.\n");
        status = 1;
    }

    term_networking();
    return status;
}
