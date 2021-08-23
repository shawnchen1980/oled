/**
 ******************************************************************************
 * @file    stream_frame.h
 * @author  Terry
 * @version v1.0.0
 * @date    2021-06-02
 * @brief   
 ******************************************************************************
 * @attention  2021-06-02 创建文件
 *
 *
 ******************************************************************************
 */

#ifndef _STREAM_FRAME_H
#define _STREAM_FRAME_H

/* includes ------------------------------------------------------------------*/
#include "stdint.h"

/* private defines -----------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
struct StreamBuffer
{
    uint8_t buffer[128];
    int index;
};

struct StreamStruct
{
    uint8_t header[2];
    uint8_t type;
    uint8_t direction;
    uint8_t command;
    uint8_t size;
    uint8_t payload[122];
};

union stream_frame
{
    struct StreamBuffer streamBuffer;
    struct StreamStruct streamStruct;
};

struct stream_ops
{
    void (*init)(void *handler);
    void (*build)(void *handler, uint8_t type, uint8_t command, uint8_t *payload, uint8_t size, struct StreamBuffer *buffer);
    void (*parse)(void *handler, uint8_t *data, uint8_t size, void (*callback)(struct StreamStruct *frame));
};

typedef struct
{
    union stream_frame frame;
    struct stream_ops *ops;
} stream_frame_type;

/* export variables prototypes -----------------------------------------------*/

/* exported functions prototypes ---------------------------------------------*/
stream_frame_type *stream_frame_create_handler(void);

#endif /* _STREAM_FRAME_H */

/**
 * @}
 */
/*************************End of File******************************************/
