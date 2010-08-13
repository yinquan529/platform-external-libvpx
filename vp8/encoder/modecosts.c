/*
 *  Copyright (c) 2010 The VP8 project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license and patent
 *  grant that can be found in the LICENSE file in the root of the source
 *  tree. All contributing project authors may be found in the AUTHORS
 *  file in the root of the source tree.
 */


#include "blockd.h"
#include "onyx_int.h"
#include "treewriter.h"
#include "entropymode.h"


void vp8_init_mode_costs(VP8_COMP *c)
{
    VP8_COMMON *x = &c->common;
    {
        const vp8_tree_p T = vp8_bmode_tree;

        int i = 0;

        do
        {
            int j = 0;

            do
            {
                vp8_cost_tokens((int *)c->mb.bmode_costs[i][j], x->kf_bmode_prob[i][j], T);
            }
            while (++j < VP8_BINTRAMODES);
        }
        while (++i < VP8_BINTRAMODES);

        vp8_cost_tokens((int *)c->mb.inter_bmode_costs, x->fc.bmode_prob, T);
    }
    vp8_cost_tokens((int *)c->mb.inter_bmode_costs, x->fc.sub_mv_ref_prob, vp8_sub_mv_ref_tree);

    vp8_cost_tokens(c->mb.mbmode_cost[1], x->fc.ymode_prob, vp8_ymode_tree);
    vp8_cost_tokens(c->mb.mbmode_cost[0], x->kf_ymode_prob, vp8_kf_ymode_tree);

    vp8_cost_tokens(c->mb.intra_uv_mode_cost[1], x->fc.uv_mode_prob, vp8_uv_mode_tree);
    vp8_cost_tokens(c->mb.intra_uv_mode_cost[0], x->kf_uv_mode_prob, vp8_uv_mode_tree);
}