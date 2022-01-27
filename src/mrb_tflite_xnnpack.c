#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <mruby.h>
#include <mruby/proc.h>
#include <mruby/data.h>
#include <mruby/numeric.h>
#include <mruby/string.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <tensorflow/lite/c/c_api.h>
#include <tensorflow/lite/delegates/xnnpack/xnnpack_delegate.h>

#if 1
#define ARENA_SAVE \
  int ai = mrb_gc_arena_save(mrb);
#define ARENA_RESTORE \
  mrb_gc_arena_restore(mrb, ai);
#else
#define ARENA_SAVE
#define ARENA_RESTORE
#endif

static void
mrb_tflite_xnnpack_delegate_free(mrb_state *mrb, void *p) {
  TfLiteXNNPackDelegateDelete((TfLiteDelegate*)p);
}

static const struct mrb_data_type mrb_tflite_xnnpack_delegate_type = {
  "mrb_tflite_xnnpack_delegate", mrb_tflite_xnnpack_delegate_free,
};

static mrb_value
mrb_tflite_xnnpack_init(mrb_state *mrb, mrb_value self) {
  TfLiteDelegate* delegate;
  TfLiteXNNPackDelegateOptions options;
  mrb_int threads;

  mrb_get_args(mrb, "i", &threads);
	options = TfLiteXNNPackDelegateOptionsDefault();
	options.num_threads = threads;
	delegate = TfLiteXNNPackDelegateCreate(&options);
  if (delegate == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "cannot create delegate");
  }
  DATA_TYPE(self) = &mrb_tflite_xnnpack_delegate_type;
  DATA_PTR(self) = delegate;
  return self;
}
void
mrb_mruby_tflite_xnnpack_gem_init(mrb_state* mrb) {
  struct RClass *_class_tflite, *_class_tflite_xnnpack;
  ARENA_SAVE;

  _class_tflite = mrb_define_module(mrb, "TfLite");
  _class_tflite_xnnpack = mrb_define_class_under(mrb, _class_tflite, "XNNPACK", mrb->object_class);

  mrb_define_method(mrb, _class_tflite_xnnpack, "initialize", mrb_tflite_xnnpack_init, MRB_ARGS_REQ(1));
  ARENA_RESTORE;
}

void
mrb_mruby_tflite_xnnpack_gem_final(mrb_state* mrb) {
}

/* vim:set et ts=2 sts=2 sw=2 tw=0: */
