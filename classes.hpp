#pragma once

/*
 * The classes Quiz, Question, and the enum QuestionType solely exists for creating quizzes
*/


std::vector<std::string> mixItUp(std::vector<std::string> vector) {
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(vector), std::end(vector), rng);
    return vector;
}

enum QuestionType {
    MultipleChoice,  // TODO: Make Example Questions of this type
    TrueOrFalse,
    Estimation,  // TODO: Make Example Questions of this type
    NONE
};

// Could also be a struct
class Question {
private:
    QuestionType _questionType;
    std::vector<std::string> _wrongAnswers;
    std::string _rightAnswer;
public:
    std::vector<std::string> AllAnswers;
    std::string QuestionSentence;
    Question(QuestionType questiontype, std::string question,
            std::vector<std::string> wronganswers, std::string rightanswer) {
        _questionType = questiontype;
        _wrongAnswers = wronganswers;
        _rightAnswer = rightanswer;
        QuestionSentence = question;
        AllAnswers = std::vector(_wrongAnswers);
        AllAnswers.push_back(_rightAnswer);
        AllAnswers = mixItUp(AllAnswers);
    }

    int GetIndexOfRightAnswer() {
         return std::find(AllAnswers.begin(), AllAnswers.end(), _rightAnswer) - AllAnswers.begin();
    }
};

class Quiz {
public: 
    std::vector<Question> Questions;
    Quiz(std::vector<Question> questions){
        Questions = questions;
    }
};


