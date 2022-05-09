
#ifndef MS912X_H
#define MS912X_H

#include <linux/mm_types.h>
#include <linux/usb.h>

#include <drm/drm_device.h>
#include <drm/drm_framebuffer.h>
#include <drm/drm_gem.h>
#include <drm/drm_simple_kms_helper.h>

#define DRIVER_NAME		"ms912x"
#define DRIVER_DESC		"MacroSilicon USB to VGA/HDMI"
#define DRIVER_DATE		"20220101"

#define DRIVER_MAJOR		0
#define DRIVER_MINOR		0
#define DRIVER_PATCHLEVEL	1


struct ms912x_device {
	struct drm_device drm;
	struct usb_interface *intf;
	struct device *dmadev;

	struct drm_connector connector;
	struct drm_simple_display_pipe display_pipe;
	struct completion transfer_done;
};

struct ms912x_request {
    u8 type;
    __be16 addr;
    u8 data[5];
} __attribute__ ((packed));

struct ms912x_write_request {
    u8 type;
    u8 addr;
	u8 data[6];
} __attribute__ ((packed));

struct ms912x_resolution_request {
	__be16 width;
	__be16 height;
	__be16 pixel_format;
} __attribute__ ((packed));

struct ms912x_mode_request {
	__be16 mode;
	__be16 width;
	__be16 height;
} __attribute__ ((packed));

// ff 00 (00 = offset left, multiple of 16) (0x00 = offset top, top half) (1b = offset top) (0x01 = width, multiple of 16) (16 bit height)
struct ms912x_frame_update_header {
	__be16 header;
	u8 x;
	__be16 y;
	u8 width;
	__be16 height;
} __attribute__ ((packed));

struct ms912x_mode {
	int width;
	int height;
	int hz;
	int mode;
	int pix_fmt;
};

#define MS912X_PIXFMT_UYVY	0x2200
#define MS912X_PIXFMT_RGB	0x1100

#define MS912X_MODE(w, h, z, m, f) \
	{ \
		.width = w, \
 		.height = h, \
 		.hz = z, \
		.mode = m, \
		.pix_fmt = f \
	}

#define MS912X_MAX_TRANSFER_LENGTH 65536

#define to_ms912x(x) container_of(x, struct ms912x_device, drm)

int ms912x_read_byte(struct ms912x_device *ms912x, u16 address);
int ms912x_connector_init(struct ms912x_device* ms912x);
int ms912x_set_resolution(struct ms912x_device *ms912x, const struct ms912x_mode* mode);

int ms912x_power_on(struct ms912x_device *ms912x);
int ms912x_power_off(struct ms912x_device *ms912x);
#endif