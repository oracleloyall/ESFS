/*
  This file is part of ESFS, a FUSE-based filesystem that supports snapshots.
  ESFS is Copyright (C) 2013 Elod Csirmaz
  <http://www.epcsirmaz.com/> <https://github.com/csirmaz>.

  ESFS is based on Big Brother File System (fuse-tutorial)
  Copyright (C) 2012 Joseph J. Pfeiffer, Jr., Ph.D. <pfeiffer@cs.nmsu.edu>,
  and was forked from it on 21 August 2013.
  Big Brother File System can be distributed under the terms of
  the GNU GPLv3. See the file COPYING.
  See also <http://www.cs.nmsu.edu/~pfeiffer/fuse-tutorial/>.

  Big Brother File System was derived from function prototypes found in
  /usr/include/fuse/fuse.h
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
  fuse.h is licensed under the LGPLv2.

  ESFS is free software: you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software
  Foundation, either version 3 of the License, or (at your option) any later
  version.

  ESFS is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
  details.

  You should have received a copy of the GNU General Public License along
  with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * NOTE: A Perl script is used to replace $ with esfs_ and $$ with ESFS_
 * in this file. To write $, use \$.
 */

/*
  There are a couple of symbols that need to be #defined before
  #including all the headers.
*/

#ifndef _PARAMS_H_
#define _PARAMS_H_

// The FUSE API has been changed a number of times.  So, our code
// needs to define the version of the API that we assume.  As of this
// writing, the most current API version is 26
#define FUSE_USE_VERSION 26

// For libraries
// -------------

// need this to get pwrite().  I have to use setvbuf() instead of
// setlinebuf() later in consequence.
#define _XOPEN_SOURCE 500

// Needed to get utimensat and AT_FDCWD
// Backtrace: fcntl.h, sys/stat.h <- features.h 
#define _ATFILE_SOURCE 1

// Parameters
// ----------
#define $log(...) log_msg(__VA_ARGS__)
#define $dlog(...) fprintf(fsdata->logfile, __VA_ARGS__)
#define $dlogi(...) fprintf(fsdata->logfile, __VA_ARGS__) // important log lines

// Constants
// ---------

/* About $$PATH_MAX
 * http://sysdocs.stu.qmul.ac.uk/sysdocs/Comment/FuseUserFileSystems/FuseBase.html
 * suggests that operations need to be thread-safe, although pkg-config does
 * not return -D_REENTRANT on my system. // TODO
 * Using a constant-length string to store the mapped path appears to be the
 * simplest solution under these circumstances, even though incoming paths
 * can be of any length.
 */
#define $$PATH_MAX PATH_MAX

// The snapshots directory
//                  1234567890
#define $$SNDIR    "/snapshots"
#define $$SNDIR_LEN 10 // Without null character

#define $$XA_TEST "$test"
#define $$XA_LATEST_SN "$latest_snapshot"
#define $$XA_PREV_SN "$prev_snapshot"
#define $$XA_NO_FILE "$no_file"

// Global FS private data
// ----------------------

#include <limits.h>
#include <stdio.h>

struct $fsdata_t {
    FILE *logfile;
    char *rootdir; // the underlying root acting as the source of the FS
    size_t rootdir_len; // length of rootdir string, without terminating NULL
    char snapshotdir[$$PATH_MAX]; // the path to the snapshot directory
};

// Retrieve and cast
#define $$FSDATA ((struct $fsdata_t *) fuse_get_context()->private_data )

// In case it matters
// ------------------
#define likely(x) (__builtin_expect((x), 1))
#define unlikely(x) (__builtin_expect((x), 0))
   
#endif
