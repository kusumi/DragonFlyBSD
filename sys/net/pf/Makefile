KMOD=	pf
SRCS=	if_pflog.c if_pfsync.c pf.c pf_if.c pf_ioctl.c pf_norm.c pf_osfp.c pf_subr.c
SRCS+=	pf_table.c pf_ruleset.c
SRCS+=	use_bpf.h use_pflog.h opt_inet.h opt_inet6.h opt_carp.h
SRCS+=	opt_icmp_bandlim.h

use_pflog.h:
	echo "#define NPFLOG 1" > ${.TARGET}

.if !defined(BUILDING_WITH_KERNEL)
opt_carp.h:
	touch ${.TARGET}

opt_inet.h:
	echo "#define INET 1" > ${.TARGET}

opt_inet6.h:
	echo "#define INET6 1" > ${.TARGET}

use_bpf.h:
	echo "#define NBPF 1" > ${.TARGET}

.endif	# !BUILDING_WITH_KERNEL


.include <bsd.kmod.mk>
