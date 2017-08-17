/*
 * librecast.h - The librecast API
 * 
 */

#include <sys/types.h>
#include <stdint.h>

#define LIBRECASTD_NOT_RUNNING 0
#define LIBRECASTD_RUNNING 1

typedef struct lc_ctx_t lc_ctx_t;
typedef struct lc_socket_t lc_socket_t;
typedef struct lc_channel_t lc_channel_t;

typedef struct lc_message_t {
	uint32_t sockid;
	char *msg;
	size_t len;
} lc_message_t;

/* create new librecast context and set up environment */
lc_ctx_t * lc_ctx_new();

/* return structure ids */
uint32_t lc_ctx_get_id(lc_ctx_t *ctx);
uint32_t lc_socket_get_id(lc_socket_t *sock);
uint32_t lc_channel_get_id(lc_channel_t *chan);

/* destroy librecast context and clean up */
void lc_ctx_free(lc_ctx_t *ctx);

/* create librecast socket */
lc_socket_t *lc_socket_new(lc_ctx_t *ctx);

/* non-blocking socket listener, with callbacks */
int lc_socket_listen(lc_socket_t *sock, void (*callback_msg)(lc_message_t*),
			                void (*callback_err)(int));

/* stop listening on socket */
int lc_socket_listen_cancel(lc_socket_t *sock);

/* close socket */
void lc_socket_close(lc_socket_t *sock);

/* create a new channel handle */
lc_channel_t * lc_channel_new(lc_ctx_t *ctx, char * url);

/* bind channel to socket */
int lc_channel_bind(lc_socket_t *sock, lc_channel_t * channel);

/* unbind channel from socket */
int lc_channel_unbind(lc_channel_t * channel);

/* join librecast channel */
int lc_channel_join(lc_channel_t * channel);

/* leave a librecast channel */
int lc_channel_part(lc_channel_t * channel);

/* free channel */
int lc_channel_free(lc_channel_t * channel);

/* return socket bound to this channel */
lc_socket_t *lc_channel_socket(lc_channel_t * channel);

/* return raw socket bound to this channel */
int lc_channel_socket_raw(lc_channel_t * channel);

/* return raw socket fd for this socket */
int lc_socket_raw(lc_socket_t *sock);

/* blocking message receive */
ssize_t lc_msg_recv(lc_socket_t *sock, char **msg);

/* send a message to a channel */
int lc_msg_send(lc_channel_t *channel, char *msg, size_t len);

/* Is librecast running?  */
int lc_librecast_running();

/* join multicast group by address
 * src can be NULL for ASM mode, or a valid source address for SSM */
int lc_joingroupbyaddr(unsigned char *addr, char *src);

/* join named multicast group
 * groupname is hashed and XORed with the base multicast address
 * src can be NULL for ASM mode, or a valid source address for SSM */
int lc_joingroupbyname(char*groupname, char *src);

