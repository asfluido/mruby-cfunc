//
//  CFunc initializer method in C
// 
//  See Copyright Notice in cfunc.h
//

#include "cfunc.h"

#include "cfunc_call.h"
#include "cfunc_pointer.h"
#include "cfunc_struct.h"
#include "cfunc_closure.h"
#include "cfunc_type.h"
#include "cfunc_rubyvm.h"

#include "mruby/proc.h"
#include "mruby/dump.h"

#include <setjmp.h>


mrb_value
cfunc_mrb_state(mrb_state *mrb, mrb_value klass)
{
    return cfunc_pointer_new_with_pointer(mrb, mrb, false);
}

void
mrb_mruby_cfunc_gem_init(mrb_state* mrb)
{
    if(sizeof(mrb_int) < 8) {
        fprintf(stderr, "mruby-cfunc require 64bit for mrb_int.");
    }

    struct RClass *ns = mrb_define_module(mrb, "CFunc");
    struct cfunc_state *state = mrb_malloc(mrb, sizeof(struct cfunc_state));
    set_cfunc_state(mrb, ns, state);

    init_cfunc_type(mrb, ns);
    init_cfunc_pointer(mrb, ns);
    init_cfunc_struct(mrb, ns);
    init_cfunc_closure(mrb, ns);
    init_cfunc_call(mrb, ns);
    init_cfunc_rubyvm(mrb, ns);

    mrb_define_class_method(mrb, ns, "mrb_state", cfunc_mrb_state, ARGS_NONE());
}
