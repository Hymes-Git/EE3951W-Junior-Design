/*
 * File:   Bufflib.h
 * Author: gahym
 *
 * Created on March 31, 2023, 4:23 PM
 */

#ifndef BUFFLIB_H
#define BUFFLIB_H

#ifdef __cplusplus
extern "C"
{
#endif

    void put_val(int newValue);

    int get_avg();

    void init_buffer();

#ifdef __cplusplus
}
#endif

#endif /* BUFFLIB_H */
