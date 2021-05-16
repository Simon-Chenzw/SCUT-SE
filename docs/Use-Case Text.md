# Just Ask
## Use-case Specification
## Version <1.0>
---
### Revision History

| Date | Version | Description | Author |
| :----: | :----: | :----: | :----: |
| 2021/04/13 | 1.0 | First draft. | Lost_Deviation |
| 2021/04/13 | 2.0 | Add some use case. | Lost_Deviation |


## Just Ask

### Introduction  
#### Purpose
    This report describes the use-case model comprehensively, in terms of how the model is structured into packages and what use cases and actors there are in the model.
#### Definitions, Acronyms and Abbreviations
    See Glossary.
#### References
    Glossary.

### Use-Case: < Register >
#### Brief Description
    User registration personal account

#### Actor Brief Descriptions
    User: the subject of questions and answers

#### Preconditions
    None

#### Stakeholders and Interests:
    1. The server should determine whether the user name is registered 
    2. The web page should determine whether the user password is a weak password

#### Basic Flow of Events
    1. The user enters the user name 
    2. The user enters the password 
    3. User confirm password 
    4. User registration is successful

    The use case ends.

#### Alternative Flows
    1a. Username is already in use 
        1.	Prompt to change user name 
    2a. User password is weak 
        1.	Prompt to change the password 
    3a The user entered the password incorrectly twice 
        1. Prompt for input errors

#### Post-conditions
    Update relevant data. Jump to login page

#### Special Requirements
    The web page should prompt the user of the characteristics of a strong password (consisting of uppercase letters, lowercase letters and numbers, and at least eight digits)

#### Additional Information:
    Frequency of Occurrence: Only occurs when the user is registered.


### Use-Case: < Login >
#### Brief Description
    User login personal account

#### Actor Brief Descriptions
    User: the subject of questions and answers

#### Preconditions
    User is already registered

#### Stakeholders and Interests:
    1. The server should determine whether the user name is registered 
    2. The server should determine whether the user password is correct

#### Basic Flow of Events
    1. The user enters the user name 
    2. The user enters the password 
    3. User login successfully
    The use case ends.

#### Alternative Flows
    1a. Username does not exist
        1. Prompt to change user name
        2. Prompt to register.
    2a. User password is incorrect
        1. Prompt that the password is wrong

#### Post-conditions
    Update relevant data. Jump to the landing page

#### Special Requirements   
    None

#### Additional Information:
    Frequency of Occurrence: Occurs only when the user logs in. average value

### Use-Case: < Ask Question >
#### Brief Description
    User asks a question

#### Actor Brief Descriptions
    User: the subject of questions and answers 
    Question: The subject of interaction with the user is only proposed by a single user, can be modified by multiple users, and can be answered by multiple users

#### Preconditions
    User has logged in

#### Stakeholders and Interest:
    The server should add the question to the question list 
    Web pages should limit the length of user questions


#### Basic Flow of Events
    1. The user enters the question title 
    2. The user enters a description of the Question 
    3. The user asks the question successfully

    The use case ends.

#### Alternative Flows
    1a. Question name is too long
        1. Prompt to replace short question name
    1b: No question name entered
        1. Prompt for question name
    2c: No question description entered 
        1.Prompt for question description

#### Post-conditions
    Update relevant data. Jump to the Question page

#### Special Requirements   
    None

#### Additional Information:
    Frequency of Occurrence: Occurs only when the user asks a question.

### Use-Case: < Modify Question >
#### Brief Description
    User modification Question

#### Actor Brief Descriptions
    User: the subject of questions and answers 
    Question: The subject of interaction with the user is only proposed by a single user, can be modified by multiple users, and can be answered by multiple users

#### Preconditions
    The user is logged in and the question has been created

#### Stakeholders and Interests:
    1. The server should update the database 
    2. Web pages should limit the length of user questions

#### Basic Flow of Events
    1. The user enters the question title 
    2. The user enters a description of the Question 3. User modification is successful
    
    The use case ends.

#### Alternative Flows
    1a. Question name is too long
        2. Prompt to replace short question name
    1b: No question name entered
        2. Prompt for question name
    2c: No question description entered 
        1.Prompt for question description


#### Post-conditions
    Update relevant data. Jump to the Question page

#### Special Requirements   
    None

#### Additional Information:
    Frequency of Occurrence: Occurs only when the user asks a question. average value
### Use-Case: < Answer Question >
#### Brief Description
    User answers questions

#### Actor Brief Descriptions
    User: the subject of questions and answers 
    Question: The subject of interaction with the user is only proposed by a single user, can be modified by multiple users, and can be answered by multiple users 
    Answer: The subject interacting with the question, a single answer can only be modified by the user who answered the question, and the user can only modify his own answer

#### Preconditions
    The user is logged in, the question has been created, and the user has not answered the question

#### Stakeholders and Interests:
    1. The server should update the database
    2. The web page should determine whether the user has answered

#### Basic Flow of Events
    1. The user enters an answer 
    2. The user answered successfully The end of the use case.
    
    The use case ends.

#### Alternative Flows
    1a: The user has already answered the question
        1. Guided answer modification interface.

#### Post-conditions
    Update relevant data. Jump to the answer page

#### Special Requirements   
    None

#### Additional Information:
    Frequency of Occurrence: Occurs only when the user answers.


### Use-Case: < Modify Answer >
#### Brief Description
    User modify answer

#### Actor Brief Descriptions
    User: the subject of questions and answers 
    Question: The subject of interaction with the user is only proposed by a single user, can be modified by multiple users, and can be answered by multiple users 
    Answer: The subject interacting with the question, a single answer can only be modified by the user who answered the question, and the user can only modify his own answer.

#### Preconditions
    The user has logged in, the question has been created, and the user has answered the question

#### Stakeholders and Interests:
    1. The server should update the database 
    2. The web page should determine whether the user has answered

#### Basic Flow of Events
    1. User modify answer 
    2. User modification is successful
    
    The use case ends.

#### Alternative Flows
    1a. The user has not answered the question 
        1. Guided answer interface

#### Post-conditions
    Update relevant data. Jump to the answer page

#### Special Requirements   
    None

#### Additional Information:
    Frequency of Occurrence: Occurs only when the user modifies the answer.

### Use-Case: < Search >
#### Brief Description
    User search questions and answers

#### Actor Brief Descriptions
    User: the subject of questions and answers 
    Question: The subject of interaction with the user is only proposed by a single user, can be modified by multiple users, and can be answered by multiple users 
    Answer: The subject interacting with the question, a single answer can only be modified by the user who answered the question, and the user can only modify his own answer

#### Preconditions
    The user is logged in.

#### Stakeholders and Interests:
    1. The server should return search result


#### Basic Flow of Events
    1. User searches for questions and answers 
    2. The server returns the result The end of the use case.

    The use case ends.

#### Alternative Flows
    1a. The user clicks search without entering anything 
        1.prompt to enter search content

#### Post-conditions
    Jump to search page

#### Special Requirements   
    None

#### Additional Information:
    Frequency of Occurrence: Occurs only when users search for questions and answers.
