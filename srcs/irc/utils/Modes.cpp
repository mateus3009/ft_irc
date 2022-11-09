#include "irc/utils/Modes.hpp"

Modes::Modes(const unsigned int& modes) : _modes(modes) {}

Modes::~Modes() {}

unsigned int Modes::getModes(void) const { return _modes; }

bool Modes::hasAnyModes(const unsigned int& modes) { return !(_modes ^ modes); }

bool Modes::hasAllModes(const unsigned int& modes) { return _modes & modes; }

void Modes::setModes(const unsigned int& modes) { _modes |= modes; }

void Modes::unsetModes(const unsigned int& modes) { _modes &= ~modes; }
