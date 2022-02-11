/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <libinit_dalvik_heap.h>
#include <libinit_utils.h>

#include "vendor_init.h"
#include <sys/stat.h>
#include <sys/types.h>

/* From Magisk@jni/magiskhide/hide_utils.c */
static const char *snet_prop_key[] = {
  "ro.boot.vbmeta.device_state",
  "ro.boot.verifiedbootstate",
  "ro.boot.flash.locked",
  "ro.boot.selinux",
  "ro.boot.veritymode",
  "ro.boot.warranty_bit",
  "ro.warranty_bit",
  "ro.debuggable",
  "ro.secure",
  "ro.build.type",
  "ro.build.tags",
  "ro.build.selinux",
  NULL
};

static const char *snet_prop_value[] = {
  "locked",
  "green",
  "1",
  "enforcing",
  "enforcing",
  "0",
  "0",
  "0",
  "1",
  "user",
  "release-keys",
  "1",
  NULL
};

static void workaround_snet_properties() {

  // Hide all sensitive props
  for (int i = 0; snet_prop_key[i]; ++i) {
    property_override(snet_prop_key[i], snet_prop_value[i]);
  }
}

void vendor_load_properties() {
    set_dalvik_heap();

    // Workaround SafetyNet
    workaround_snet_properties();
}