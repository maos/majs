export SRCROOT := ${PWD}
export CoMT_DIR := ${PWD}/complement/explore
SUBDIRS :=  classifier

-include ${SRCROOT}/Makefiles/gmake/config.mak

ifndef WITHOUT_STLPORT
LIBSUBDIRS := STLport
else
LIBSUBDIRS := 
endif

LIBSUBDIRS += complement/explore/lib/misc \
							complement/explore/lib/mt

include ${SRCROOT}/Makefiles/gmake/subdirs.mak

all:
	+$(call doinsubdirs,${LIBSUBDIRS} ${SUBDIRS})

release-shared:
	+$(call doinsubdirs,${LIBSUBDIRS} ${SUBDIRS})

dbg-shared:
	+$(call doinsubdirs,${LIBSUBDIRS} ${SUBDIRS})

ifndef WITHOUT_STLPORT
stldbg-shared:
	+$(call doinsubdirs,${LIBSUBDIRS} ${SUBDIRS})
endif

depend:
	+$(call doinsubdirs,${LIBSUBDIRS} ${SUBDIRS})

clean mostlyclean distclean:
	+$(call doinsubdirs,${LIBSUBDIRS} ${SUBDIRS})

maintainer-clean:
	+$(call doinsubdirs,${LIBSUBDIRS} ${SUBDIRS})

check-release-shared:	release-shared
	+$(call doinsubdirs,${LIBSUBDIRS},LD_LIBRARY_PATH=${PWD}/STLport/src/obj/gcc/so)

check-dbg-shared:	dbg-shared
	+$(call doinsubdirs,${LIBSUBDIRS},LD_LIBRARY_PATH=${PWD}/STLport/src/obj/gcc/so)

ifndef WITHOUT_STLPORT
check-stldbg-shared:	stldbg-shared
	+$(call doinsubdirs,${LIBSUBDIRS},LD_LIBRARY_PATH=${PWD}/STLport/src/obj/gcc/so)
endif

.PHONY: all depend clean mostlyclean distclean maintainer-clean \
        release-shared dbg-shared stldbg-shared \
        check check-release-shared check-dbg-shared check-stldbg-shared

