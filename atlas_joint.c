#include "atlas_joint.h"
#include "atlas_utility.h"

bool atlas_joint_reference_is_equal(atlas_joint_reference_t const* reference1,
                                    atlas_joint_reference_t const* reference2)
{
    ATLAS_ASSERT(reference1 != NULL);
    ATLAS_ASSERT(reference2 != NULL);

    return reference1->delta_time == reference2->delta_time &&
           reference2->position == reference2->position;
}

void atlas_joint_reference_print(atlas_joint_reference_t const* reference)
{
    ATLAS_ASSERT(reference != NULL);

    atlas_log("reference position: %f, delta_time: %f\n\r",
              reference->position,
              reference->delta_time);
}

bool atlas_joint_measure_is_equal(atlas_joint_measure_t const* measure1,
                                  atlas_joint_measure_t const* measure2)
{
    ATLAS_ASSERT(measure1 != NULL);
    ATLAS_ASSERT(measure2 != NULL);

    return measure1->current == measure1->current &&
           measure1->position == measure2->position;
}

void atlas_joint_measure_print(atlas_joint_measure_t const* measure)
{
    ATLAS_ASSERT(measure != NULL);

    atlas_log("measure position: %f, measure: %f\n\r",
              measure->position,
              measure->current);
}
