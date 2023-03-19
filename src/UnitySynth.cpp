#ifdef __cplusplus
extern "C" {
#endif

UNITY_INTERFACE_EXPORT void* UNITY_INTERFACE_API getInstance()
{
    return githappens::UnityWrapper::instance;
}

UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API noteOn(void* ptr, int noteNumber, float velocity)
{
    jassert(ptr != nullptr);
    githappens::UnitySynth* synth = static_cast<githappens::UnitySynth*>(ptr);
    synth->noteOn(1, noteNumber, velocity);
}

UNITY_INTERFACE_EXPORT void UNITY_INTERFACE_API noteOff(void* ptr, int noteNumber)
{
    jassert(ptr != nullptr);
    githappens::UnitySynth* synth = static_cast<githappens::UnitySynth*>(ptr);
    synth->noteOff(1, noteNumber, 1);
}

#ifdef __cplusplus
}
#endif


namespace githappens::UnityWrapper
{
    githappens::UnitySynth* instance = nullptr;
}

githappens::UnitySynth::UnitySynth(juce::MidiKeyboardState& state)
: _keyboardState(state)
{
}

githappens::UnitySynth::~UnitySynth()
{
    if(UnityWrapper::instance == this)
        UnityWrapper::instance = nullptr;
}

void githappens::UnitySynth::initialize()
{
    UnityWrapper::instance = this;
}

void githappens::UnitySynth::noteOn(int channel, int noteNumber, float velocity)
{
    _keyboardState.noteOn(channel, noteNumber, velocity);
}

void githappens::UnitySynth::noteOff(int channel, int noteNumber, float velocity)
{
    _keyboardState.noteOff(channel, noteNumber, velocity);
}
