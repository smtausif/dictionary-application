#include "dictionary.h"
#include "settings.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace seneca {

    const char* partOfSpeechToStr(PartOfSpeech pos) {
        switch (pos) {
            case PartOfSpeech::Noun: return "noun";
            case PartOfSpeech::Pronoun: return "pronoun";
            case PartOfSpeech::Adjective: return "adjective";
            case PartOfSpeech::Adverb: return "adverb";
            case PartOfSpeech::Verb: return "verb";
            case PartOfSpeech::Preposition: return "preposition";
            case PartOfSpeech::Conjunction: return "conjunction";
            case PartOfSpeech::Interjection: return "interjection";
            default: return "";
        }
    }

    Dictionary::Dictionary() = default;

    Dictionary::~Dictionary() {
        delete[] m_words;
    }

    Dictionary::Dictionary(const Dictionary& src) {
        m_size = src.m_size;
        m_words = new Word[m_size];
        for (size_t i = 0; i < m_size; ++i)
            m_words[i] = src.m_words[i];
    }

    Dictionary& Dictionary::operator=(const Dictionary& src) {
        if (this != &src) {
            delete[] m_words;
            m_size = src.m_size;
            m_words = new Word[m_size];
            for (size_t i = 0; i < m_size; ++i)
                m_words[i] = src.m_words[i];
        }
        return *this;
    }

    Dictionary::Dictionary(Dictionary&& other) {
        m_words = other.m_words;
        m_size = other.m_size;
        other.m_words = nullptr;
        other.m_size = 0;
    }

    Dictionary& Dictionary::operator=(Dictionary&& other) {
        if (this != &other) {
            delete[] m_words;
            m_words = other.m_words;
            m_size = other.m_size;
            other.m_words = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    PartOfSpeech Dictionary::parsePos(const std::string& posStr) const {
        if (posStr == "n." || posStr == "n. pl.") return PartOfSpeech::Noun;
        if (posStr == "adv.") return PartOfSpeech::Adverb;
        if (posStr == "a.") return PartOfSpeech::Adjective;
        if (posStr == "v." || posStr == "v. i." || posStr == "v. t." || posStr == "v. t. & i.") return PartOfSpeech::Verb;
        if (posStr == "prep.") return PartOfSpeech::Preposition;
        if (posStr == "pron.") return PartOfSpeech::Pronoun;
        if (posStr == "conj.") return PartOfSpeech::Conjunction;
        if (posStr == "interj.") return PartOfSpeech::Interjection;
        return PartOfSpeech::Unknown;
    }

    Dictionary::Dictionary(const char* filename) {
        std::ifstream file(filename);
        if (!file) {
            m_words = nullptr;
            m_size = 0;
            return;
        }

        std::string line;
        size_t capacity = 100;
        m_words = new Word[capacity];
        m_size = 0;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string word, pos, def;

            std::getline(ss, word, ',');
            std::getline(ss, pos, ',');
            std::getline(ss, def);

            if (m_size == capacity) {
                capacity *= 2;
                Word* temp = new Word[capacity];
                for (size_t i = 0; i < m_size; ++i)
                    temp[i] = m_words[i];
                delete[] m_words;
                m_words = temp;
            }

            m_words[m_size].m_word = word;
            m_words[m_size].m_pos = parsePos(pos);
            m_words[m_size].m_definition = def;
            m_size++;
        }
    }

    void Dictionary::searchWord(const char* word) const {
        bool found = false;
        size_t indent = 0;

        for (size_t i = 0; i < m_size; ++i) {
            if (m_words[i].m_word == word) {
                if (!found) {
                    std::cout << m_words[i].m_word;
                    indent = m_words[i].m_word.length();
                } else {
                    std::cout << std::setw(indent) << ' ';
                }

                if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                    std::cout << " - (" << partOfSpeechToStr(m_words[i].m_pos) << ") ";
                } else {
                    std::cout << " - ";
                }

                std::cout << m_words[i].m_definition << std::endl;
                found = true;

                if (!g_settings.m_show_all) return;
            }
        }

        if (!found) {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }
    }

}
