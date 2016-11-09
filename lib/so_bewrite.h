#ifndef SO_BEWRITE_H_
#define SO_BEWRITE_H_

/*
 * sonata.
 *
 * Protocol-level PostgreSQL client library.
*/

static inline int
so_bewrite_error(sostream_t *buf, char *message, int len)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t) + len + 1);
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, 'E');
	so_stream_write32(buf, sizeof(uint32_t) + len);
	so_stream_write(buf, (uint8_t*)message, len);
	so_stream_write8(buf, 0);
	return 0;
}

static inline int
so_bewrite_notice(sostream_t *buf, char *message, int len)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t) + len + 1);
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, 'N');
	so_stream_write32(buf, sizeof(uint32_t) + len);
	so_stream_write(buf, (uint8_t*)message, len);
	so_stream_write8(buf, 0);
	return 0;
}

static inline int
so_bewrite_authentication(sostream_t *buf, uint32_t status)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t) + sizeof(uint32_t));
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, 'R');
	so_stream_write32(buf, sizeof(uint32_t) + sizeof(status));
	so_stream_write32(buf, status);
	return 0;
}

static inline int
so_bewrite_backend_key_data(sostream_t *buf, uint32_t pid, uint32_t key)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t) +
	                      sizeof(uint32_t) +
	                      sizeof(uint32_t));
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, 'K');
	so_stream_write32(buf, sizeof(uint32_t) + sizeof(uint32_t) +
	              sizeof(uint32_t));
	so_stream_write32(buf, pid);
	so_stream_write32(buf, key);
	return 0;
}

static inline int
so_bewrite_parameter_status(sostream_t *buf, char *key, int key_len,
                            char *value, int value_len)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t) + key_len + value_len);
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, 'S');
	so_stream_write32(buf, sizeof(uint32_t) + key_len + value_len);
	so_stream_write(buf, (uint8_t*)key, key_len);
	so_stream_write(buf, (uint8_t*)value, value_len);
	return 0;
}

static inline int
so_bewrite_ready(sostream_t *buf, uint8_t status)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t) + sizeof(uint8_t));
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, 'Z');
	so_stream_write32(buf, sizeof(uint32_t) + sizeof(uint8_t));
	so_stream_write8(buf, status);
	return 0;
}

/* row description */
/* datarow */

static inline int
so_bewrite_complete(sostream_t *buf, char *message, int len)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t) + len);
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, 'C');
	so_stream_write32(buf, sizeof(uint32_t) + len);
	so_stream_write(buf, (uint8_t*)message, len);
	return 0;
}

static inline int
so_bewrite_empty_query(sostream_t *buf)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t));
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, 'I');
	so_stream_write32(buf, sizeof(uint32_t));
	return 0;
}

static inline int
so_bewrite_parse_complete(sostream_t *buf)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t));
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, '1');
	so_stream_write32(buf, sizeof(uint32_t));
	return 0;
}

static inline int
so_bewrite_bind_complete(sostream_t *buf)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t));
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, '2');
	so_stream_write32(buf, sizeof(uint32_t));
	return 0;
}

static inline int
so_bewrite_portal_suspended(sostream_t *buf)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t));
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, 's');
	so_stream_write32(buf, sizeof(uint32_t));
	return 0;
}

static inline int
so_bewrite_no_data(sostream_t *buf)
{
	int rc = so_stream_ensure(buf, sizeof(soheader_t));
	if (so_unlikely(rc == -1))
		return -1;
	so_stream_write8(buf, 'n');
	so_stream_write32(buf, sizeof(uint32_t));
	return 0;
}

#endif
