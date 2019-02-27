// Unless explicitly stated otherwise all files in this repository are licensed
// under the Apache License Version 2.0.
// This product includes software developed at Datadog (https://www.datadoghq.com/).
// Copyright 2019 Datadog, Inc.
#ifndef DATADOG_AGENT_SIX_TYPES_H
#define DATADOG_AGENT_SIX_TYPES_H
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DATADOG_AGENT_SIX_API
#    ifdef DATADOG_AGENT_SIX_TEST
#        define DATADOG_AGENT_SIX_API
#    elif _WIN32
#        define DATADOG_AGENT_SIX_API __declspec(dllexport)
#    else
#        if __GNUC__ >= 4
#            define DATADOG_AGENT_SIX_API __attribute__((visibility("default")))
#        else
#            define DATADOG_AGENT_SIX_API
#        endif
#    endif
#endif

#ifndef WIN32
#    define _strdup(x) strdup(x)
#endif

typedef enum six_gilstate_e { DATADOG_AGENT_SIX_GIL_LOCKED, DATADOG_AGENT_SIX_GIL_UNLOCKED } six_gilstate_t;

typedef enum six_module_func_e {
    DATADOG_AGENT_SIX_NOARGS,
    DATADOG_AGENT_SIX_ARGS,
    DATADOG_AGENT_SIX_KEYWORDS
} six_module_func_t;

typedef enum six_module_e {
    DATADOG_AGENT_SIX__UTIL = 0,
    DATADOG_AGENT_SIX_AGGREGATOR,
    DATADOG_AGENT_SIX_CONTAINERS,
    DATADOG_AGENT_SIX_DATADOG_AGENT,
    DATADOG_AGENT_SIX_KUBEUTIL,
    DATADOG_AGENT_SIX_TAGGER,
    DATADOG_AGENT_SIX_UTIL,
} six_module_t;

typedef enum {
    DATADOG_AGENT_SIX_GAUGE = 0,
    DATADOG_AGENT_SIX_RATE,
    DATADOG_AGENT_SIX_COUNT,
    DATADOG_AGENT_SIX_MONOTONIC_COUNT,
    DATADOG_AGENT_SIX_COUNTER,
    DATADOG_AGENT_SIX_HISTOGRAM,
    DATADOG_AGENT_SIX_HISTORATE
} metric_type_t;

typedef struct event_t {
    char *title;
    char *text;
    long ts;
    char *priority;
    char *host;
    char **tags;
    int tags_num;
    char *alert_type;
    char *aggregation_key;
    char *source_type_name;
    char *event_type;
} event_t;

// custom builtins
//
// aggregator
//
// (id, metric_type, metric_name, value, tags, tags_len, hostname)
typedef void (*cb_submit_metric_t)(char *, metric_type_t, char *, float, char **, int, char *);
// (id, sc_name, status, tags, tags_len, hostname, message)
typedef void (*cb_submit_service_check_t)(char *, char *, int, char **, int, char *, char *);
// (id, event)
typedef void (*cb_submit_event_t)(char *, event_t *);

// these strings need to be alive for the whole interpreter lifetime because
// they'll be used from the CPython Inittab. Be sure to keep these in sync
// with `six_module_e` contents.
static const char *datadog_agent_six_unknown = "";
static const char *datadog_agent_six__util = "_util";
static const char *datadog_agent_six_aggregator = "aggregator";
static const char *datadog_agent_six_containers = "containers";
static const char *datadog_agent_six_datadog_agent = "datadog_agent";
static const char *datadog_agent_six_kubeutil = "kubeutil";
static const char *datadog_agent_six_tagger = "tagger";
static const char *datadog_agent_six_util = "util";

#ifdef __cplusplus
}
#endif
#endif