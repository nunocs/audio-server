#include "cshim.h"

extern "C" {

core_t* new_core()
{
    auto retv = new Core;
    //printf("new_core: %p\n", retv);
    return AS_TYPE(core_t*, retv);
}


void set_period(core_t* core, int32_t size)
{
    AS_TYPE(Core*, core)->setPeriodSize(size);
}


int16_t get_wave_index(core_t* core, const char* filename)
{
    return AS_TYPE(Core*, core)->getWaveIndex(filename);
}

int16_t add_wave(core_t* core, uint32_t size, uint8_t channels, const int16_t *samples)
{
    SoundBuffer *sb = new SoundBuffer(size, channels);
    memcpy(sb->getData(), samples, size * channels * sizeof(int16_t));
    return AS_TYPE(Core*, core)->addWave(sb);
}

int16_t add_generator(core_t* core, int32_t type)
{
    return AS_TYPE(Core*, core)->addGenerator(static_cast<generator::types>(type));
}


void configure_generator(core_t* core, uint16_t gid, generator_cfg_t* cfg)
{
    AS_TYPE(Core*, core)->generatorConfig(gid, AS_TYPE(generator::ConfigData*, cfg));
}


int16_t add_source(core_t* core)
{
    return AS_TYPE(Core*, core)->addSource();
}


void configure_source(core_t* core, uint16_t sid, source_cfg_t* cfg)
{
    AS_TYPE(Core*, core)->sourceConfig(sid, AS_TYPE(processor::SourceConfigData*, cfg));
}


void set_source_generator(core_t* core, uint16_t sid, uint16_t gid)
{
    AS_TYPE(Core*, core)->setSourceGenerator(sid, gid);
}


void set_processor(core_t* core, int32_t type)
{
    AS_TYPE(Core*, core)->setProcessor(static_cast<processor::types>(type));
}


void configure_processor(core_t* core, processor_cfg_t* cfg)
{
    AS_TYPE(Core*, core)->processorConfig(AS_TYPE(processor::ConfigData*, cfg));
}


void set_output(core_t* core, int32_t type)
{
    AS_TYPE(Core*, core)->setOutput(static_cast<output::types>(type));
}


void configure_output(core_t* core, output_cfg_t* cfg)
{
    AS_TYPE(Core*, core)->outputConfig(AS_TYPE(output::ConfigData*, cfg));
}


void render(core_t* core, int32_t periods)
{
    for (int i = 0; i < periods; i++) {
        AS_TYPE(Core*, core)->render();
    }
}


void stop_output(core_t* core)
{
    AS_TYPE(Core*, core)->stop_output();
}


int16_t *get_output(core_t* core, uint64_t *size, bool clear)
{
    int16_t *dest;
    *size = AS_TYPE(Core*, core)->get_output(&dest, clear);
    return dest;
}


void free_output(core_t* core, int16_t *mem)
{
    delete [] mem;
}


void del_core(core_t* core)
{
    //printf("del_core: %p\n", core);
    AS_TYPE(Core*, core)->shutdown();
    delete AS_TYPE(Core*, core);
}

void reset(core_t* core, bool reset_output)
{
    AS_TYPE(Core*, core)->reset(reset_output);
}

} // extern "C"
