/*
 * Copyright (c) 2015 Broadcom
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * 3. Neither the name of Broadcom nor the names of other contributors to this
 * software may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * 4. This software may not be used as a standalone product, and may only be used as
 * incorporated in your product or device that incorporates Broadcom wireless connectivity
 * products and solely for the purpose of enabling the functionalities of such Broadcom products.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY WARRANTIES OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT, ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Setup options for NetX */

#ifndef NX_USER_H
#define NX_USER_H

#define WICED_CUSTOM_NX_USER_H

/* Set system to little Endian */
#define NX_LITTLE_ENDIAN

/* Setup the characteristics of the Physical layer */
#define NX_PHYSICAL_HEADER          (14 + 12 + 22 )
#define NX_PHYSICAL_TRAILER         (0)
#undef NX_LINK_MTU

#define NX_DHCP_PACKET_PAYLOAD      (NX_BOOT_BUFFER_SIZE + NX_PHYSICAL_HEADER + 20 + 8 + 4 + 4)

/* prevent sending reset for non-blocking disconnect */
/* Checksum generation for UDP seems to be broken at least in v5.4 */
#define NX_DISABLE_UDP_TX_CHECKSUM
#define NX_FTP_NO_FILEX
#define NX_HTTP_NO_FILEX
#define NX_TFTP_NO_FILEX
#define NX_DISABLE_RESET_DISCONNECT
#define NX_ARP_DISABLE_AUTO_ARP_ENTRY
#define NX_DHCP_CLIENT_RESTORE_STATE

#define NX_TCP_ENABLE_KEEPALIVE

#define NX_TCP_MAX_OUT_OF_ORDER_PACKETS

#define NX_MAX_LISTEN_REQUESTS 18

#define PACKET_RELEASE_NOTIFY
extern void packet_release_notify( void* pool );
extern UINT nx_rand16( void );


/* Disable parameter checking when building non-debug */
#ifndef DEBUG
#define NX_DISABLE_ERROR_CHECKING
#else
#undef NX_DISABLE_ERROR_CHECKING
#endif







/* Disable NetX information gathering */
#define NX_DISABLE_ARP_INFO
#define NX_DISABLE_IP_INFO
#define NX_DISABLE_ICMP_INFO
#define NX_DISABLE_IGMP_INFO
#define NX_DISABLE_PACKET_INFO
#define NX_DISABLE_RARP_INFO
#define NX_DISABLE_TCP_INFO
#define NX_DISABLE_UDP_INFO

extern unsigned long host_rtos_get_tickrate( void );

#define NX_IP_PERIODIC_RATE ( host_rtos_get_tickrate( ) )

#define NX_RANDOM_INITIAL_TCP_PORT

#define NX_ARP_DISABLE_AUTO_ARP_ENTRY


/* These are all the defines that are used in NetX-Duo #if statements
 * This prevents users changing NetX values to become incompatible with
 * the prebuilt libraries.
 *
 */





#undef __NETXDUO_MAJOR_VERSION__
#undef __NETXDUO_MINOR_VERSION__
#undef __time_t_defined
#undef OK
#undef SO_PASSCRED
/* #undef TX_ENABLE_EVENT_TRACE */
#undef FD_SETSIZE
#undef ERROR
#undef fd_set
#undef FIONBIO
#undef FIONREAD
#undef htonl
#undef htons
#undef ntohl
#undef ntohs

#undef MULTI_HOMED_DEVICE
#undef AUTHENTICATION_REQUIRED
#undef DEFAULT_SESSION_RUN
#undef EL_PRINTF_ENABLE
#undef FD_SETSIZE
#undef FEATURE_NX_IPV6
#undef MULTI_HOME_NETX
#undef FILEX_STUB_H


#undef PACKET_DUMP
#undef PRIVACY_REQUIRED
#undef REQUEST_CLIENT_IP
#undef REQUEST_IP_ADDRESS
#undef SEND_INIT_UNICAST
#undef SEND_V3_TRAP
#undef SKIP_DISCOVER_MESSAGE
#undef TESTOUTPUT

#undef USE_SHA
#undef NX_ARP_EXPIRATION_RATE
#undef NX_ARP_MAX_QUEUE_DEPTH
#undef NX_ARP_MAXIMUM_RETRIES
#undef NX_ARP_UPDATE_RATE
#undef NX_AUTO_IP_ANNOUNCE_INTERVAL
#undef NX_AUTO_IP_ANNOUNCE_NUM
#undef NX_AUTO_IP_ANNOUNCE_WAIT
#undef NX_AUTO_IP_DEBUG
#undef NX_AUTO_IP_DEFEND_INTERVAL
#undef NX_AUTO_IP_MAX_CONFLICTS
#undef NX_AUTO_IP_PROBE_MAX
#undef NX_AUTO_IP_PROBE_MIN
#undef NX_AUTO_IP_PROBE_NUM
#undef NX_AUTO_IP_PROBE_WAIT
#undef NX_AUTO_IP_RATE_LIMIT_INTERVAL
#undef NX_BSD_INCLUDE_DATA_EXTRACT_OFFSET
#undef NX_BSD_INHERIT_LISTENER_SOCKET_SETTINGS
#undef NX_BSD_INHERIT_LISTENER_SOCKET_SETTINGS
#undef NX_BSD_LINGER_TIMER_RATE
#undef NX_BSD_MAX_LISTEN_BACKLOG
#undef NX_BSD_MAX_SOCKETS
#undef NX_BSD_PRINT_ERRORS
#undef NX_BSD_SOCKFD_START
#undef NX_BSD_TCP_WINDOW
#undef NX_BSD_TIMED_WAIT_TIMEOUT
#undef NX_BSD_TIMEOUT
#undef NX_BSD_TW_TIMER_RATE
#undef NX_CPU_TICKS_PER_SECOND
#undef NX_DEBUG
#undef NX_DEBUG_PACKET
#undef NX_DHCP_ARP_PROBE_TIMEOUT
#undef NX_DHCP_CLIENT_HOSTNAME_MAX
#undef NX_DHCP_CLIENT_IDENTIFIER_MAX
#undef NX_DHCP_CLIENT_OPTIONS_MAX
#undef NX_DHCP_CLIENT_RECORD_TABLE_SIZE
/* #undef NX_DHCP_CLIENT_SEND_ARP_PROBE */
#undef NX_DHCP_CLIENT_SESSION_TIMEOUT
#undef NX_DHCP_DEFAULT_LEASE_TIME
#undef NX_DHCP_ENABLE_BOOTP
#undef NX_DHCP_FAST_PERIODIC_TIME_INTERVAL
#undef NX_DHCP_FRAGMENT_OPTION
#undef NX_DHCP_INCLUDE_PACKET_DATA_EXTRACT_OFFSET
#undef NX_DHCP_IP_ADDRESS_MAX_LIST_SIZE
#undef NX_DHCP_MAX_RETRANS_TIMEOUT
#undef NX_DHCP_MIN_RENEW_TIMEOUT
#undef NX_DHCP_MIN_RETRANS_TIMEOUT
#undef NX_DHCP_MINIMUM_PACKET_PAYLOAD
#undef NX_DHCP_OPTIONAL_SERVER_OPTION_LIST
#undef NX_DHCP_OPTIONAL_SERVER_OPTION_SIZE
#undef NX_DHCP_PACKET_ALLOCATE_TIMEOUT
#undef NX_DHCP_PACKET_POOL_SIZE
#undef NX_DHCP_QUEUE_DEPTH
#undef NX_DHCP_SERVER_HOSTNAME_MAX
#undef NX_DHCP_SERVER_NAME
#undef NX_DHCP_SERVER_THREAD_PRIORITY
#undef NX_DHCP_SERVER_THREAD_STACK_SIZE
#undef NX_DHCP_SLOW_PERIODIC_TIME_INTERVAL
#undef NX_DHCP_SUBNET_MASK
#undef NX_DHCP_THREAD_PRIORITY
#undef NX_DHCP_THREAD_STACK_SIZE
#undef NX_DHCP_TIME_INTERVAL
#undef NX_DHCP_TIME_TO_LIVE
#undef NX_DHCP_TIMEOUT_DECREMENTS
#undef NX_DHCP_TYPE_OF_SERVICE
#undef NX_DIRECT_ISR_CALL
#undef NX_DISABLE_EXTENDED_NOTIFY_SUPPORT
#undef NX_DISABLE_FRAGMENTATION
#undef NX_DISABLE_IGMPV2
#undef NX_DISABLE_IP_RX_CHECKSUM
#undef NX_DISABLE_IP_TX_CHECKSUM
#undef NX_DISABLE_LOOPBACK_INTERFACE
#undef NX_DISABLE_RX_SIZE_CHECKING
#undef NX_DISABLE_TCP_RX_CHECKSUM
#undef NX_DISABLE_TCP_TX_CHECKSUM
#undef NX_DISABLE_UDP_RX_CHECKSUM
#undef NX_DNS_FRAGMENT_OPTION
#undef NX_DNS_MAX_SERVERS
#undef NX_DNS_TIME_TO_LIVE
#undef NX_DNS_TYPE_OF_SERVICE
#undef NX_DRIVER_DEFERRED_PROCESSING
#undef NX_ENABLE_IP_STATIC_ROUTING
#undef NX_ENABLE_IP_STATIC_ROUTING
#undef NX_EXTENDED_BSD_ENABLE_ASYNCH_ACCEPT
#undef NX_EXTENDED_BSD_SOCKET_SUPPORT
#undef NX_EXTENDED_BSD_SOCKET_SUPPORT
#undef NX_EXTENDED_BSD_SOCKET_SUPPORT
#undef NX_EXTENDED_BSD_SOCKET_SUPPORT
#undef NX_FTP_ACTIVITY_TIMEOUT
#undef NX_FTP_CONTROL_TOS
#undef NX_FTP_CONTROL_WINDOW_SIZE
#undef NX_FTP_DATA_TOS
#undef NX_FTP_DATA_WINDOW_SIZE
#undef NX_FTP_FAULT_TOLERANT
#undef NX_FTP_FRAGMENT_OPTION
#undef NX_FTP_MAX_CLIENTS
#undef NX_FTP_PASSWORD_SIZE
#undef NX_FTP_SERVER_PRIORITY
#undef NX_FTP_SERVER_RETRY_MAX
#undef NX_FTP_SERVER_RETRY_SECONDS
#undef NX_FTP_SERVER_RETRY_SHIFT
#undef NX_FTP_SERVER_TIME_SLICE
#undef NX_FTP_SERVER_TIMEOUT
#undef NX_FTP_SERVER_TRANSMIT_QUEUE_DEPTH
#undef NX_FTP_TIME_TO_LIVE
#undef NX_FTP_TIMEOUT_PERIOD
#undef NX_FTP_USERNAME_SIZE
#undef NX_HTTP_CLIENT_MIN_PACKET_SIZE
#undef NX_HTTP_DIGEST_ENABLE
#undef NX_HTTP_FRAGMENT_OPTION
#undef NX_HTTP_MAX_NAME
#undef NX_HTTP_MAX_PASSWORD
#undef NX_HTTP_MAX_RESOURCE
#undef NX_HTTP_SERVER_MAX_PENDING
#undef NX_HTTP_SERVER_MIN_PACKET_SIZE
#undef NX_HTTP_SERVER_OMIT_CONTENT_LENGTH
#undef NX_HTTP_SERVER_PRIORITY
#undef NX_HTTP_SERVER_RETRY_MAX
#undef NX_HTTP_SERVER_RETRY_SECONDS
#undef NX_HTTP_SERVER_RETRY_SHIFT
#undef NX_HTTP_SERVER_THREAD_TIME_SLICE
#undef NX_HTTP_SERVER_TIMEOUT
#undef NX_HTTP_SERVER_TRANSMIT_QUEUE_DEPTH
#undef NX_HTTP_SERVER_WINDOW_SIZE
#undef NX_HTTP_TIME_TO_LIVE
#undef NX_HTTP_TYPE_OF_SERVICE
#undef NX_IP_DEBUG_LOG_SIZE
#undef NX_IP_RAW
#undef NX_IP_ROUTING_TABLE_SIZE
#undef NX_IP_STATUS_CHECK_WAIT_TIME
/* #undef NX_MAX_LISTEN_REQUESTS */
#undef NX_MAX_MULTICAST_GROUPS
#undef NX_MAX_PHYSICAL_INTERFACES
#undef NX_MICROSECOND_PER_CPU_TICK
#undef NX_MULTIHOME_SUPPORT
#undef NX_NAT_ALLOW_INBOUND_BROADCAST_PACKETS
#undef NX_NAT_ALLOW_OUTBOUND_BROADCAST_PACKETS
#undef NX_NAT_ARP_CACHE_SIZE
#undef NX_NAT_BYTE_POOL_MUTEX_NAME
#undef NX_NAT_BYTE_POOL_MUTEX_WAIT
#undef NX_NAT_BYTE_POOL_NAME
#undef NX_NAT_BYTE_POOL_SIZE
#undef NX_NAT_DEBUG
#undef NX_NAT_DISABLE_ERROR_CHECKING
#undef NX_NAT_DISABLE_TRANSLATION_TABLE_INFO
#undef NX_NAT_DISABLE_WHOLE_ICMP_RX_CHECKSUM
#undef NX_NAT_DISABLE_WHOLE_ICMP_TX_CHECKSUM
#undef NX_NAT_DISABLE_WHOLE_IP_CHECKSUM
#undef NX_NAT_DISABLE_WHOLE_TCP_RX_CHECKSUM
#undef NX_NAT_DISABLE_WHOLE_TCP_TX_CHECKSUM
#undef NX_NAT_DISABLE_WHOLE_UDP_RX_CHECKSUM
#undef NX_NAT_DISABLE_WHOLE_UDP_TX_CHECKSUM
#undef NX_NAT_ENABLE_FRAGMENT_RECEIVE
#undef NX_NAT_ENABLE_FRAGMENTATION
#undef NX_NAT_ENABLE_ZERO_UDP_CHECKSUM
#undef NX_NAT_ENABLED
#undef NX_NAT_ENABLED
#undef NX_NAT_ENABLED
#undef NX_NAT_END_ICMP_QUERY_ID
#undef NX_NAT_FTP_CONTROL_PORT
#undef NX_NAT_FTP_DATA_PORT
#undef NX_NAT_GLOBAL_NETMASK
#undef NX_NAT_IP_THREAD_PRIORITY
#undef NX_NAT_IP_THREAD_STACK_SIZE
#undef NX_NAT_MAX_ICMP_MESSAGE_SIZE
#undef NX_NAT_MAX_UDP_RX_QUEUE
#undef NX_NAT_MILLISECONDS_PER_TICK
#undef NX_NAT_PACKET_ALLOCATE_TIMEOUT
#undef NX_NAT_PACKET_POOL_SIZE
#undef NX_NAT_PACKET_QUEUE_TIMEOUT
#undef NX_NAT_PACKET_SIZE
#undef NX_NAT_PREEMPTION_THRESHOLD
#undef NX_NAT_PRIVATE_NETMASK
#undef NX_NAT_REFRESH_TIMER_ON_INBOUND_PACKETS
#undef NX_NAT_START_ICMP_QUERY_ID
#undef NX_NAT_TABLE_ENTRY_RESPONSE_TIMEOUT
#undef NX_NAT_TABLE_MUTEX_WAIT
#undef NX_NAT_TCP_PORT_BIND_TIMEOUT
#undef NX_NAT_THREAD_PRIORITY
#undef NX_NAT_THREAD_STACK_SIZE
#undef NX_NAT_THREAD_TIME_SLICE
#undef NX_NAT_TICKS_PER_SECOND
#undef NX_NAT_TIMER_TIMEOUT_INTERVAL
#undef NX_NAT_TRANSLATION_TABLE_MAX_ENTRIES
#undef NX_NAT_UDP_PORT_BIND_TIMEOUT
#undef NX_PACKET_ALLOCATE_TIMEOUT
#undef NX_PACKET_HEADER_PAD
#undef NX_PACKET_HEADER_PAD_SIZE
#undef NX_PACKET_OFFSET_ERROR
#undef NX_POP3_CLIENT_ARP_CACHE_SIZE
#undef NX_POP3_CLIENT_BLOCK_POOL_MUTEX_NAME
#undef NX_POP3_CLIENT_BLOCK_POOL_MUTEX_WAIT
#undef NX_POP3_CLIENT_BLOCK_POOL_NAME
#undef NX_POP3_CLIENT_BLOCK_POOL_SIZE
#undef NX_POP3_CLIENT_BLOCK_SIZE
#undef NX_POP3_CLIENT_BYTE_POOL_MUTEX_NAME
#undef NX_POP3_CLIENT_BYTE_POOL_MUTEX_WAIT
#undef NX_POP3_CLIENT_BYTE_POOL_NAME
#undef NX_POP3_CLIENT_BYTE_POOL_SIZE
#undef NX_POP3_CLIENT_CONNECTION_TIMEOUT
#undef NX_POP3_CLIENT_DEBUG
#undef NX_POP3_CLIENT_DELETE_MAIL_ON_SERVER
#undef NX_POP3_CLIENT_DISCONNECT_TIMEOUT
#undef NX_POP3_CLIENT_DYNAMIC_MEMORY_ALLOC
#undef NX_POP3_CLIENT_H
#undef NX_POP3_CLIENT_IP_THREAD_PRIORITY
#undef NX_POP3_CLIENT_IP_THREAD_STACK_SIZE
#undef NX_POP3_CLIENT_IPADR
#undef NX_POP3_CLIENT_MAIL_BUFFER_SIZE
#undef NX_POP3_CLIENT_PACKET_POOL_SIZE
#undef NX_POP3_CLIENT_PACKET_SIZE
#undef NX_POP3_CLIENT_PACKET_TIMEOUT
#undef NX_POP3_CLIENT_PREEMPTION_THRESHOLD
#undef NX_POP3_CLIENT_REPLY_TIMEOUT
#undef NX_POP3_CLIENT_SESSION_COUNT
#undef NX_POP3_CLIENT_SESSION_PREEMPTION_THRESHOLD
#undef NX_POP3_CLIENT_SESSION_THREAD_PRIORITY
#undef NX_POP3_CLIENT_SESSION_THREAD_STACK_SIZE
#undef NX_POP3_CLIENT_SESSION_THREAD_TIME_SLICE
#undef NX_POP3_CLIENT_TCP_SOCKET_NAME
#undef NX_POP3_CLIENT_THREAD_PRIORITY
#undef NX_POP3_CLIENT_THREAD_STACK_SIZE
#undef NX_POP3_CLIENT_THREAD_TIME_SLICE
#undef NX_POP3_CLIENT_WINDOW_SIZE
#undef NX_POP3_DISABLE_ERROR_CHECKING
#undef NX_POP3_ENABLE_PRINTF
#undef NX_POP3_MAX_CLIENT_PASSWORD
#undef NX_POP3_MAX_CLIENT_SECRET
#undef NX_POP3_MAX_CLIENT_USERNAME
#undef NX_POP3_MAX_CLOCK_TIME
#undef NX_POP3_MAX_PASSWORD
#undef NX_POP3_MAX_PROCESS_ID
#undef NX_POP3_MAX_SERVER_APOP_STRING
#undef NX_POP3_MAX_SERVER_SESSIONS
#undef NX_POP3_MAX_SHARED_SECRET
#undef NX_POP3_MAX_USERNAME
#undef NX_POP3_PRINT_SERVER_RESERVES
#undef NX_POP3_SERVER_ARP_CACHE_SIZE
#undef NX_POP3_SERVER_BYTE_POOL_MUTEX_NAME
#undef NX_POP3_SERVER_BYTE_POOL_MUTEX_WAIT
#undef NX_POP3_SERVER_BYTE_POOL_NAME
#undef NX_POP3_SERVER_BYTE_POOL_SIZE
#undef NX_POP3_SERVER_CONNECTION_TIMEOUT
#undef NX_POP3_SERVER_DEBUG
#undef NX_POP3_SERVER_DEFAULT_PROCESS_ID
#undef NX_POP3_SERVER_DEFAULT_TIME
#undef NX_POP3_SERVER_DISCONNECT_TIMEOUT
#undef NX_POP3_SERVER_DOMAIN
#undef NX_POP3_SERVER_H
#undef NX_POP3_SERVER_IP_THREAD_PRIORITY
#undef NX_POP3_SERVER_IP_THREAD_STACK_SIZE
#undef NX_POP3_SERVER_MAX_MAILDROP_COUNT
#undef NX_POP3_SERVER_MAX_REPLY
#undef NX_POP3_SERVER_PACKET_POOL_SIZE
#undef NX_POP3_SERVER_PACKET_SIZE
#undef NX_POP3_SERVER_PACKET_TIMEOUT
#undef NX_POP3_SERVER_PORT
#undef NX_POP3_SERVER_PREEMPTION_THRESHOLD
#undef NX_POP3_SERVER_PRINT_TIMEOUT
#undef NX_POP3_SERVER_SESSION_PORT
#undef NX_POP3_SERVER_SESSION_PREEMPTION_THRESHOLD
#undef NX_POP3_SERVER_SESSION_THREAD_PRIORITY
#undef NX_POP3_SERVER_SESSION_THREAD_STACK_SIZE
#undef NX_POP3_SERVER_SESSION_THREAD_TIME_SLICE
#undef NX_POP3_SERVER_SOCKET_QUEUE_SIZE
#undef NX_POP3_SERVER_TCP_RECEIVE_TIMEOUT
#undef NX_POP3_SERVER_TCP_SOCKET_SEND_WAIT
#undef NX_POP3_SERVER_THREAD_PRIORITY
#undef NX_POP3_SERVER_THREAD_STACK_SIZE
#undef NX_POP3_SERVER_THREAD_TIME_SLICE
#undef NX_POP3_SERVER_WINDOW_SIZE
#undef NX_POP3_TCP_SOCKET_SEND_WAIT
#undef NX_PPP_DEBUG_FRAME_SIZE
#undef NX_PPP_DEBUG_LOG_ENABLE
#undef NX_PPP_DEBUG_LOG_PRINT_ENABLE
#undef NX_PPP_DEBUG_LOG_SIZE
#undef NX_PPP_DISABLE_CHAP
#undef NX_PPP_DISABLE_INFO
#undef NX_PPP_DISABLE_PAP
#undef NX_PPP_HASHED_VALUE_SIZE
#undef NX_PPP_MINIMUM_MRU
#undef NX_PPP_MRU
#undef NX_PPP_NAME_SIZE
#undef NX_PPP_PASSWORD_SIZE
#undef NX_PPP_RECEIVE_TIMEOUT
#undef NX_PPP_SERIAL_BUFFER_SIZE
#undef NX_PPP_THREAD_TIME_SLICE
#undef NX_PPP_TIMEOUT
#undef NX_PPP_TIMEOUT_RETRIES
#undef NX_PPP_VALUE_SIZE
#undef NX_SMTP_CLIENT_ARP_CACHE_SIZE
#undef NX_SMTP_CLIENT_AUTHENTICATION_LIST
#undef NX_SMTP_CLIENT_BLOCK_POOL_MUTEX_NAME
#undef NX_SMTP_CLIENT_BLOCK_POOL_MUTEX_WAIT
#undef NX_SMTP_CLIENT_BLOCK_POOL_NAME
#undef NX_SMTP_CLIENT_BLOCK_POOL_SIZE
#undef NX_SMTP_CLIENT_BLOCK_SIZE
#undef NX_SMTP_CLIENT_BYTE_POOL_MUTEX_NAME
#undef NX_SMTP_CLIENT_BYTE_POOL_MUTEX_WAIT
#undef NX_SMTP_CLIENT_BYTE_POOL_NAME
#undef NX_SMTP_CLIENT_BYTE_POOL_SIZE
#undef NX_SMTP_CLIENT_CONNECTION_TIMEOUT
#undef NX_SMTP_CLIENT_DEBUG
#undef NX_SMTP_CLIENT_DOMAIN
#undef NX_SMTP_CLIENT_IP_STACK_SIZE
#undef NX_SMTP_CLIENT_IP_THREAD_PRIORITY
#undef NX_SMTP_CLIENT_MESSAGE_ID_SIZE
#undef NX_SMTP_CLIENT_NO_MEM_ALLOC
#undef NX_SMTP_CLIENT_PACKET_HEADER_SIZE
#undef NX_SMTP_CLIENT_PACKET_POOL_SIZE
#undef NX_SMTP_CLIENT_PACKET_SIZE
#undef NX_SMTP_CLIENT_PREEMPTION_THRESHOLD
#undef NX_SMTP_CLIENT_PRINT_TIMEOUT
#undef NX_SMTP_CLIENT_PRIORITY
#undef NX_SMTP_CLIENT_SESSION_COMMAND_RETRIES
#undef NX_SMTP_CLIENT_SESSION_COUNT
#undef NX_SMTP_CLIENT_SESSION_PORT
#undef NX_SMTP_CLIENT_SESSION_PRIORITY
#undef NX_SMTP_CLIENT_SESSION_RESETS
#undef NX_SMTP_CLIENT_SESSION_STACK_SIZE
#undef NX_SMTP_CLIENT_SESSION_THREAD_TIME_SLICE
#undef NX_SMTP_CLIENT_STACK_SIZE
#undef NX_SMTP_CLIENT_TCP_SOCKET_NAME
#undef NX_SMTP_CLIENT_THREAD_TIME_SLICE
#undef NX_SMTP_CLIENT_WINDOW_SIZE
#undef NX_SMTP_DATA_TRANSPARENCY_BYTES
#undef NX_SMTP_DATE_AND_TIME_STAMP_SIZE
#undef NX_SMTP_DISABLE_ERROR_CHECKING
#undef NX_SMTP_DISCONNECT_TIMEOUT
#undef NX_SMTP_ENCRYPTION_MAX_STRING
#undef NX_SMTP_ENVELOPE_TIMEOUT_TICKS
#undef NX_SMTP_GREETING_TIMEOUT_TICKS
#undef NX_SMTP_MAX_AUTH_LIST
#undef NX_SMTP_MAX_DOMAIN_NAME
#undef NX_SMTP_MAX_LOCAL_PART
#undef NX_SMTP_MAX_PASSWORD
#undef NX_SMTP_MAX_SERVER_AUTH_PROMPT
#undef NX_SMTP_MAX_SERVER_SESSIONS
#undef NX_SMTP_MAX_USERNAME
#undef NX_SMTP_MESSAGE_TIMEOUT_TICKS
#undef NX_SMTP_PACKET_TIMEOUT
#undef NX_SMTP_PRINT_CLIENT_MAIL_DATA
#undef NX_SMTP_PRINT_CLIENT_RESERVES
#undef NX_SMTP_PRINT_SERVER_MAIL_DATA
#undef NX_SMTP_PRINT_SERVER_RESERVES
#undef NX_SMTP_REPLY_BUFFER_SIZE
#undef NX_SMTP_SERVER_ACKNOWLEDGE_QUIT
#undef NX_SMTP_SERVER_ARP_CACHE_SIZE
#undef NX_SMTP_SERVER_AUTH_CANCELLED
#undef NX_SMTP_SERVER_AUTH_INTERNAL_SERVER_ERROR
#undef NX_SMTP_SERVER_AUTH_PREVIOUS_ATTEMPT
#undef NX_SMTP_SERVER_AUTH_REQUIRED
#undef NX_SMTP_SERVER_AUTHENTICATION_LIST
#undef NX_SMTP_SERVER_AUTHENTICATION_REQUIRED
#undef NX_SMTP_SERVER_AUTHENTICATION_SUCCESSFUL
#undef NX_SMTP_SERVER_AUTHENTICATION_UNSUCCESSFUL
#undef NX_SMTP_SERVER_BAD_RECIPIENT_MAILBOX_NAME
#undef NX_SMTP_SERVER_BAD_SENDERS_MAILBOX_NAME
#undef NX_SMTP_SERVER_BAD_SEQUENCE
#undef NX_SMTP_SERVER_BLOCK_POOL_MUTEX_NAME
#undef NX_SMTP_SERVER_BLOCK_POOL_MUTEX_WAIT
#undef NX_SMTP_SERVER_BLOCK_POOL_NAME
#undef NX_SMTP_SERVER_BLOCK_POOL_SIZE
#undef NX_SMTP_SERVER_BLOCK_SIZE
#undef NX_SMTP_SERVER_BYTE_POOL_MUTEX_NAME
#undef NX_SMTP_SERVER_BYTE_POOL_MUTEX_WAIT
#undef NX_SMTP_SERVER_BYTE_POOL_NAME
#undef NX_SMTP_SERVER_BYTE_POOL_SIZE
#undef NX_SMTP_SERVER_CLOSE_CONNECTION_MESSAGE
#undef NX_SMTP_SERVER_COMMAND_NOT_IMPLEMENTED
#undef NX_SMTP_SERVER_COMMAND_SYNTAX_ERROR
#undef NX_SMTP_SERVER_CONNECTION_MESSAGE
#undef NX_SMTP_SERVER_CONNECTION_TIMEOUT
#undef NX_SMTP_SERVER_DEBUG
#undef NX_SMTP_SERVER_DISCONNECT_TIMEOUT
#undef NX_SMTP_SERVER_DOMAIN
#undef NX_SMTP_SERVER_HELO_PROTOCOL
#undef NX_SMTP_SERVER_INSUFFICIENT_STORAGE
#undef NX_SMTP_SERVER_INTERNAL_SERVER_ERROR
#undef NX_SMTP_SERVER_INVALID_PACKET_DATA
#undef NX_SMTP_SERVER_IP_STACK_SIZE
#undef NX_SMTP_SERVER_IP_THREAD_PRIORITY
#undef NX_SMTP_SERVER_OK
#undef NX_SMTP_SERVER_OVERSIZE_MAIL_MESSAGE
#undef NX_SMTP_SERVER_PACKET_HEADER_SIZE
#undef NX_SMTP_SERVER_PACKET_POOL_SIZE
#undef NX_SMTP_SERVER_PACKET_SIZE
#undef NX_SMTP_SERVER_PARAMETER_NOT_IMPLEMENTED
#undef NX_SMTP_SERVER_PARAMETER_SYNTAX_ERROR
#undef NX_SMTP_SERVER_PREEMPTION_THRESHOLD
#undef NX_SMTP_SERVER_PRINT_TIMEOUT
#undef NX_SMTP_SERVER_RECIPIENT_MAIL_LIMIT
#undef NX_SMTP_SERVER_REQUESTED_ACTION_NOT_TAKEN
#undef NX_SMTP_SERVER_SERVICE_NOT_AVAILABLE
#undef NX_SMTP_SERVER_SERVICES_MESSAGE
#undef NX_SMTP_SERVER_SESSION_EXCEEDED_STORAGE_LIMIT
#undef NX_SMTP_SERVER_SESSION_MAIL_LIMIT
#undef NX_SMTP_SERVER_SESSION_PORT
#undef NX_SMTP_SERVER_SESSION_PREEMPTION_THRESHOLD
#undef NX_SMTP_SERVER_SESSION_THREAD_PRIORITY
#undef NX_SMTP_SERVER_SESSION_THREAD_STACK_SIZE
#undef NX_SMTP_SERVER_SESSION_THREAD_TIME_SLICE
#undef NX_SMTP_SERVER_SOCKET_QUEUE_SIZE
#undef NX_SMTP_SERVER_START_MAIL_INPUT
#undef NX_SMTP_SERVER_TCP_RECEIVE_TIMEOUT
#undef NX_SMTP_SERVER_TCP_SOCKET_SEND_WAIT
#undef NX_SMTP_SERVER_THREAD_PRIORITY
#undef NX_SMTP_SERVER_THREAD_STACK_SIZE
#undef NX_SMTP_SERVER_THREAD_TIME_SLICE
#undef NX_SMTP_SERVER_TOO_MANY_RECIPIENTS
#undef NX_SMTP_SERVER_TOO_MANY_SESSION_MAILS
#undef NX_SMTP_SERVER_TRANSACTION_FAILED
#undef NX_SMTP_SERVER_WINDOW_SIZE
#undef NX_SMTP_SESSION_AUTH_TYPE
#undef NX_SMTP_SESSION_PREEMPTION_THRESHOLD
#undef NX_SMTP_SETUP_CLIENT_IN_DEMO
#undef NX_SMTP_SETUP_CLIENT_IN_DEMO
#undef NX_SMTP_SETUP_SERVER_IN_DEMO
#undef NX_SMTP_SETUP_SERVER_IN_DEMO
#undef NX_SMTP_TCP_SOCKET_SEND_WAIT
#undef NX_SNMP_AGENT_PORT
#undef NX_SNMP_AGENT_PRIORITY
#undef NX_SNMP_AGENT_TIMEOUT
#undef NX_SNMP_DISABLE_V1
#undef NX_SNMP_DISABLE_V2
#undef NX_SNMP_DISABLE_V3
#undef NX_SNMP_FRAGMENT_OPTION
#undef NX_SNMP_MANAGER_TRAP_PORT
#undef NX_SNMP_MAX_CONTEXT_STRING
#undef NX_SNMP_MAX_OCTET_STRING
#undef NX_SNMP_MAX_SECURITY_KEY
#undef NX_SNMP_MAX_USER_NAME
#undef NX_SNMP_NO_SECURITY
#undef NX_SNMP_PACKET_SIZE
#undef NX_SNMP_TIME_TO_LIVE
#undef NX_SNMP_TYPE_OF_SERVICE
#undef NX_SNMP_V1_AUTHORIZATION_ERROR_RESPONSE
#undef NX_SNMP_V2C_ONLY
#undef NX_SNTP_CLIENT_ARP_CACHE_SIZE
#undef NX_SNTP_CLIENT_BAD_UPDATE_LIMIT
#undef NX_SNTP_CLIENT_BROADCAST_DOMAIN
#undef NX_SNTP_CLIENT_BROADCAST_SERVER_TIMEOUT
#undef NX_SNTP_CLIENT_DEBUG
#undef NX_SNTP_CLIENT_EXP_BACKOFF_RATE
#undef NX_SNTP_CLIENT_IGNORE_MAX_ADJUST_STARTUP
#undef NX_SNTP_CLIENT_INITIAL_UNICAST_TIMEOUT
#undef NX_SNTP_CLIENT_IP_ADDRESS
#undef NX_SNTP_CLIENT_IP_STACK_SIZE
#undef NX_SNTP_CLIENT_IP_THREAD_PRIORITY
#undef NX_SNTP_CLIENT_LOG_ENABLED
#undef NX_SNTP_CLIENT_MANYCAST_ADDRESS
#undef NX_SNTP_CLIENT_MAX_LOG_ENTRY
#undef NX_SNTP_CLIENT_MAX_QUEUE_DEPTH
#undef NX_SNTP_CLIENT_MAX_ROOT_DISPERSION
#undef NX_SNTP_CLIENT_MAX_SERVERS
#undef NX_SNTP_CLIENT_MAX_TIME_ADJUSTMENT
#undef NX_SNTP_CLIENT_MAX_TIME_LAPSE
#undef NX_SNTP_CLIENT_MIN_NTP_VERSION
#undef NX_SNTP_CLIENT_MIN_SERVER_STRATUM
#undef NX_SNTP_CLIENT_MIN_TIME_ADJUSTMENT
#undef NX_SNTP_CLIENT_MULTICAST_ADDRESS
#undef NX_SNTP_CLIENT_NTP_VERSION
#undef NX_SNTP_CLIENT_PACKET_HEADER_SIZE
#undef NX_SNTP_CLIENT_PACKET_POOL_SIZE
#undef NX_SNTP_CLIENT_PACKET_SIZE
#undef NX_SNTP_CLIENT_PACKET_TIMEOUT
#undef NX_SNTP_CLIENT_PREEMPTION_THRESHOLD
#undef NX_SNTP_CLIENT_RUN_IN_TEST_MODE
#undef NX_SNTP_CLIENT_SERVER_LIST_WAIT
#undef NX_SNTP_CLIENT_STACK_SIZE
#undef NX_SNTP_CLIENT_THREAD_PRIORITY
#undef NX_SNTP_CLIENT_THREAD_TIME_SLICE
#undef NX_SNTP_CLIENT_TIME_TO_LIVE
#undef NX_SNTP_CLIENT_UDP_PORT
#undef NX_SNTP_CLIENT_UDP_SOCKET_NAME
#undef NX_SNTP_CLIENT_UNICAST_POLL_INTERVAL
#undef NX_SNTP_CLIENT_UNICAST_SERVER_TIMEOUT
#undef NX_SNTP_DISABLE_ERROR_CHECKING
#undef NX_SNTP_UDP_BROADCAST_SERVER_ADDRESSES
#undef NX_SNTP_UDP_UNICAST_SERVER_ADDRESSES
#undef NX_SNTP_UPDATE_TIMEOUT_INTERVAL
#undef NX_TCP_ACK_EVERY_N_PACKETS
#undef NX_TCP_ACK_TIMER_RATE
#undef NX_TCP_ENABLE_DEBUG_LOG
#undef NX_TCP_ENABLE_WINDOW_SCALING
#undef NX_TCP_ENABLE_WINDOW_SCALING
#undef NX_TCP_FAST_TIMER_RATE
#undef NX_TCP_IMMEDIATE_ACK
#undef NX_TCP_KEEPALIVE_INITIAL
#undef NX_TCP_KEEPALIVE_RETRIES
#undef NX_TCP_KEEPALIVE_RETRY
#undef NX_TCP_MAXIMUM_RETRIES
#undef NX_TCP_MAXIMUM_TX_QUEUE
#undef NX_TCP_RETRY_SHIFT
#undef NX_TCP_TRANSMIT_TIMER_RATE
#undef NX_TELNET_ACTIVITY_TIMEOUT
#undef NX_TELNET_FRAGMENT_OPTION
#undef NX_TELNET_MAX_CLIENTS
#undef NX_TELNET_MAX_OPTION_SIZE
#undef NX_TELNET_SERVER_PRIORITY
#undef NX_TELNET_SERVER_TIMEOUT
#undef NX_TELNET_SERVER_WINDOW_SIZE
#undef NX_TELNET_TIME_TO_LIVE
#undef NX_TELNET_TIMEOUT_PERIOD
#undef NX_TELNET_TOS
#undef NX_TFTP_ERROR_STRING_MAX
#undef NX_TFTP_FRAGMENT_OPTION
#undef NX_TFTP_MAX_CLIENTS
#undef NX_TFTP_SERVER_PRIORITY
#undef NX_TFTP_SERVER_TIME_SLICE
#undef NX_TFTP_TIME_TO_LIVE
#undef NX_TFTP_TYPE_OF_SERVICE
#undef NX_TRACE_INTERNAL_ARP_REQUEST_RECEIVE
#undef NX_TRACE_OBJECT_TYPE_IP
#undef NX_UDP_DEBUG_LOG_SIZE

#ifdef PLATFORM_L1_CACHE_SHIFT

#include "platform_cache_def.h"

#define NX_PACKET_HEADER_SIZE     52 /* Bytes of header not counting padding. Header can be changed by stack features enabling / disabling. Static assert is added somewhere to make sure header is aligned. */
#define NX_PACKET_HEADER_PAD_SIZE ((PLATFORM_L1_CACHE_ROUND_UP(NX_PACKET_HEADER_SIZE) - NX_PACKET_HEADER_SIZE) / 4)

#if NX_PACKET_HEADER_PAD_SIZE
#define NX_PACKET_HEADER_PAD
#else
#undef NX_PACKET_HEADER_PAD_SIZE
#endif

#endif /* PLATFORM_L1_CACHE_SHIFT */

/* defined in port.h
#define TX_TIMER_PROCESS_IN_ISR
#define TX_DISABLE_ERROR_CHECKING
*/

/* defined in api.h
#define __NETX_MAJOR_VERSION__
#define __NETX_MINOR_VERSION__
*/

/* toolchain defines
#define __cplusplus
#define DEBUG
*/
#endif

