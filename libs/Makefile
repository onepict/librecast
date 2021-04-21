# SPDX-License-Identifier: GPL-2.0-or-GPL-3.0
# Copyright (c) 2017-2021 Brett Sheffield <bacs@librecast.net>

TARGETS=
ifndef USE_LIBSODIUM
TARGETS += blake3
endif

libs: $(TARGETS)

.PHONY: blake3 clean realclean

blake3:
	$(MAKE) -C blake3/c

clean realclean:
	$(MAKE) -C blake3/c $@
