#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <random>
#include <vector>

std::vector<std::string> mixItUp(std::vector<std::string> vec) {
    std::vector<std::string> retVec { };
    std::random_device seedgenerator;
    std::mt19937 numbergenerator(seedgenerator());
    std::uniform_int_distribution<> distributor(0, vec.size()-1);
    for (std::size_t i = 0; i < vec.size(); ++i){
        retVec.push_back(vec[distributor(numbergenerator)]);
    }
    return retVec;
}

enum QuestionType {
    MultipleChoice,
    TrueOrFalse,
    Estimation
};

// Could also be a struct
class Question {
private:
    QuestionType _questionType;
    std::vector<std::string> _wrongAnswers;
    std::string _rightAnswer;
public:
    std::vector<std::string> AllAnswers;
    Question(QuestionType questiontype, std::vector<std::string> wronganswers, std::string rightanswer) {
        _questionType = questiontype;
        _wrongAnswers = wronganswers;
        _rightAnswer = rightanswer;
        AllAnswers = std::vector(_wrongAnswers);
        AllAnswers.push_back(_rightAnswer);
    }

    int GetIndexOfRightAnswer() {
        // I use std::difference instead of subtracting the iterators because this produces an integer and subtracting doesn't
        return std::difference(AllAnswers.begin(), std::find(AllAnswers.begin(), AllAnswers.end(), _rightAnswer);
    }
};

class Quiz {
public:
    std::vector<Question> Questions;
    Quiz(std::vector<Question> questions) {
        Questions = questions;
    }
};

int main() {
    /*
     * TODO: Use stuff from ./examplequizzes as tests
     *
    */
    return 0;
}
