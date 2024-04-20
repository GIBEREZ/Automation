#ifndef ENUMERATION_H
#define ENUMERATION_H

/* 运行状态枚举*/
typedef enum 
{
    error = 0x0000,
    ok = 0x0001,
} Ment;

/* 截图工具枚举 */
typedef enum 
{
    Handle_NULL = 0x2100,
    Handle_error = 0x2110,

} ScreenshotFlag;

#endif