#ifndef SAMPLEPRESET_H
#define SAMPLEPRESET_H

#include <Container.h>


class SamplePreset : public Container
{
    public:
        SamplePreset();
        void initialize(float offset, Vector p0) override;
};

#endif // SAMPLEPRESET_H
