/*-
 * Copyright (c) 1999, 2000
 * Intel Corporation.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *
 *    This product includes software developed by Intel Corporation and
 *    its contributors.
 *
 * 4. Neither the name of Intel Corporation or its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY INTEL CORPORATION AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL INTEL CORPORATION OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/* From:  https://github.com/freebsd/freebsd-src/blob/main/stand/efi/libefi/time.c
 * Modified for use with RISC OS 64.
 */

#include <time.h>
#include <string.h>


/*
 * Accurate only for the past couple of centuries;
 * that will probably do.
 *
 * (#defines From FreeBSD 3.2 lib/libc/stdtime/tzfile.h)
 */

#define isleap(y)   (((y) % 4) == 0 && \
                (((y) % 100) != 0 || ((y) % 400) == 0))
#define SECSPERHOUR (60*60)
#define SECSPERDAY  (24 * SECSPERHOUR)

/*
 *  These arrays give the cumulative number of days up to the first of the
 *  month number used as the index (1 -> 12) for regular and leap years.
 *  The value at index 13 is for the whole year.
 */
static const time_t CumulativeDays[2][14] = {
    {0,
    0,
    31,
    31 + 28,
    31 + 28 + 31,
    31 + 28 + 31 + 30,
    31 + 28 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 },
    {0,
    0,
    31,
    31 + 29,
    31 + 29 + 31,
    31 + 29 + 31 + 30,
    31 + 29 + 31 + 30 + 31,
    31 + 29 + 31 + 30 + 31 + 30,
    31 + 29 + 31 + 30 + 31 + 30 + 31,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30,
    31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 }};



void
to_gm_time(struct tm *gm_time, time_t time)
{
    int lyear, month;
    time_t seconds;

    if (time >= 0) {
        gm_time->tm_wday = 0; /* Not calculated here */
        gm_time->tm_zone = 0; /* Not returned */

        gm_time->tm_year = 1970;
        lyear = isleap(gm_time->tm_year);
        month = 13;
        seconds = CumulativeDays[lyear][month] * SECSPERDAY;
        while (time > seconds) {
            time -= seconds;
            gm_time->tm_year++;
            lyear = isleap(gm_time->tm_year);
            seconds = CumulativeDays[lyear][month] * SECSPERDAY;
        }

        gm_time->tm_mon = 0;
        gm_time->tm_yday = 0;
        while (time >
            CumulativeDays[lyear][month] * SECSPERDAY) {
            gm_time->tm_yday += CumulativeDays[lyear][month];
            gm_time->tm_mon++;
        }

        month = gm_time->tm_mon - 1;
        time -= CumulativeDays[lyear][month] * SECSPERDAY;

        for (gm_time->tm_mday = 1; time > SECSPERDAY; gm_time->tm_mday++)
            time -= SECSPERDAY;
        gm_time->tm_yday += gm_time->tm_mday - 1;

        for (gm_time->tm_hour = 0; time > SECSPERHOUR; gm_time->tm_hour++)
            time -= SECSPERHOUR;

        for (gm_time->tm_min = 0; time > 60; gm_time->tm_min++)
            time -= 60;

        gm_time->tm_sec = time;

        gm_time->tm_gmtoff = 0;
        gm_time->tm_isdst = 0;
    } else {
        memset(gm_time, 0, sizeof(*gm_time));
    }
}

time_t
from_gm_time(struct tm *gm_time)
{
    time_t  UTime;
    int Year;

    /*
     *  Do a santity check
     */
    if (gm_time->tm_year  <  1998 || gm_time->tm_year   > 2099 ||
        gm_time->tm_mon ==    0 || gm_time->tm_mon  >   12 ||
        gm_time->tm_mday   ==    0 || gm_time->tm_mon  >   31 ||
        gm_time->tm_hour   >   23 || gm_time->tm_min >   59 ||
        gm_time->tm_sec >   59 || gm_time->tm_gmtoff  < -1440 ||
        (gm_time->tm_gmtoff >  1440 && gm_time->tm_gmtoff != 2047)) {
        return (0);
    }

    /*
     * Years
     */
    UTime = 0;
    for (Year = 1970; Year != gm_time->tm_year; ++Year) {
        UTime += (CumulativeDays[isleap(Year)][13] * SECSPERDAY);
    }

    /*
     * UTime should now be set to 00:00:00 on Jan 1 of the file's year.
     *
     * Months
     */
    UTime += (CumulativeDays[isleap(gm_time->tm_year)][gm_time->tm_mon] *
        SECSPERDAY);

    /*
     * UTime should now be set to 00:00:00 on the first of the file's
     * month and year.
     *
     * Days -- Don't count the file's day
     */
    UTime += (((gm_time->tm_mday > 0) ? gm_time->tm_mday-1:0) * SECSPERDAY);

    /*
     * Hours
     */
    UTime += (gm_time->tm_hour * SECSPERHOUR);

    /*
     * Minutes
     */
    UTime += (gm_time->tm_min * 60);

    /*
     * Seconds
     */
    UTime += gm_time->tm_sec;

    /*
     * EFI time is repored in local time.  Adjust for any time zone
     * offset to get true UT
     */
    if (gm_time->tm_gmtoff != -1) {
        /*
         * TimeZone is kept in minutes...
         */
        UTime += (gm_time->tm_gmtoff * 60);
    }

    return (UTime);
}

static struct tm global_tm;

struct tm *gmtime(const time_t *time)
{
    time_t tval = *time;

    to_gm_time(&global_tm, tval);
    return &global_tm;
}
