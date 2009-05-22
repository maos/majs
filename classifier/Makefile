SRCROOT := ..

include Makefile.inc
include ${SRCROOT}/complement/explore/Makefiles/gmake/top.mak

INCLUDES += -I$(SRCROOT)/include -I$(SRCROOT)/complement/explore/include

DEFS += -D_FILE_OFFSET_BITS=64

LIBMT_DIR = ${SRCROOT}/complement/explore/lib/mt
LIBSOCK_DIR = ${SRCROOT}/complement/explore/lib/sockios
LIBSTEM_DIR = ${SRCROOT}/complement/explore/lib/stem
LIBMISC_DIR = ${SRCROOT}/complement/explore/lib/misc

ifndef WITHOUT_STLPORT
STLPORT_LIB_DIR = ${SRCROOT}/STLport/src
endif

release-shared:	LDFLAGS += -L${LIBMT_DIR}/${OUTPUT_DIR} \
	-L${LIBMISC_DIR}/${OUTPUT_DIR} \
	-L${LIBSOCK_DIR}/${OUTPUT_DIR} \
	-L${LIBSTEM_DIR}/${OUTPUT_DIR} \
	-Wl,-rpath=${LIBMISC_DIR}/${OUTPUT_DIR}:${STLPORT_LIB_DIR}/${OUTPUT_DIR}

release-shared:	DEFS += -DNO_STEM_TRACE

dbg-shared:	LDFLAGS += -L${LIBMT_DIR}/${OUTPUT_DIR_DBG} \
	-L${LIBMISC_DIR}/${OUTPUT_DIR_DBG} \
	-Wl,-rpath=${LIBMISC_DIR}/${OUTPUT_DIR_DBG}:${STLPORT_LIB_DIR}/${OUTPUT_DIR_DBG}

ifndef WITHOUT_STLPORT
stldbg-shared:	LDFLAGS += -L${LIBMT_DIR}/${OUTPUT_DIR_STLDBG} \
	-L${LIBMISC_DIR}/${OUTPUT_DIR_STLDBG} \
	-Wl,-rpath=${LIBMISC_DIR}/${OUTPUT_DIR_STLDBG}:${STLPORT_LIB_DIR}/${OUTPUT_DIR_STLDBG}
endif

release-shared : LDLIBS = -lmisc -lboost_filesystem 
dbg-shared     : LDLIBS = -lmiscg 
ifndef WITHOUT_STLPORT
stldbg-shared  : LDLIBS = -lmiscstlg
endif
