// dictionary.h
#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>
#include "event.h"

namespace seneca {

    enum class PartOfSpeech {
        Unknown, Noun, Pronoun, Adjective, Adverb, Verb,
        Preposition, Conjunction, Interjection
    };

    struct Word {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class Dictionary {
        Word* m_words{};
        size_t m_size{};

        PartOfSpeech parsePos(const std::string& posStr) const;

    public:
        Dictionary();  // Default constructor
        Dictionary(const char* filename); // Custom constructor (load from CSV)
        Dictionary(const Dictionary&); // Copy constructor
        Dictionary& operator=(const Dictionary&); // Copy assignment
        Dictionary(Dictionary&&); // Move constructor
        Dictionary& operator=(Dictionary&&); // Move assignment
        ~Dictionary(); // Destructor

        void searchWord(const char* word) const; // Lookup
    };

}

#endif // SENECA_DICTIONARY_H
