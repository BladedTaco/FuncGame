
## Cleaned Notes
These notes have been cleaned to be human readable rather than stream-of-consciousness get down whatever will make me remember it later.
The Raw notes (with potentially-identifying information removed) are also available. "Quoted Sections" are direct quotes from participants.

## Participant Profile

### Functional Programming Experience
- P2 is not familiar with Functional Programming, but has head about it

### Game Experience
- P2 is "too familiar" with games
    - majority of familiarity comes from video games
    - aware of tabletop games

## Level 1

### Tutorial/Demonstration
- Nothing of note

### Phase 1
- Nothing of note, solved quickly

### Phase 2
- Confused about what the chest does despite demonstration
    - After a while figured out what needs to go into the chest
- Confused again about what was different from the demonstration with the LT wired the wrong way
    - After some time and prompting, was able to fix the error

### Post-Level discussion
- Nothing of Note

## Level 2

### Phase 1
- Solved effortlessly

### Phase 2
- Disconnected all blocks from previous phases to go back to a clean slate
    - This made solving the level more difficult

### Phase 3
- P2 started looking at the type signatures to solve levels rather than trial and error
- Struggles a bit to find how they can solve the levels problem
    - Once an idea of how to solve the level was found, was able to act on it extremely quickly to solve phase

### Phase 4
- Unsure about what const is needed for as it needed the inputs disconnected
    - Was able to figure out what it was needed for once phrasing the problem in terms of the previous phases
- Set a (0,0) position from having liftA2 inputs wrong way around
    - This turned out to be a soft-lock, and the level was ended here

### Post-Level discussion
- P2 laments that they remember the concepts of haskell, but not much of the actual language
    - P2 suggests this may be why they are having some difficulties with the game

## Level 3
- Is not able to recognise what LT, EQ, and MAX may be from the iconography

### Phase 1
- After trying out different inputs with the comparison blocks, is able to guess at what they are
    - Initially thought MAX/OR was AND
    - Seems to be due to the values switching too quickly
- Recognised the sweeping attacks position block instantly from iconography and values

### Phase 2
- Easily able to handle the comparison lower inputs turning to maybes to solve quickly

### Phase 3
- Not able to figure out >>= block
- P2 eventually gave up on level due to thinking they had spent too long on this one level
- Rest of level was demonstrated by researcher

### Phase 4
- Not attempted, but was demonstrated

### Post-Level discussion
- Participant stayed zoomed out to the point where they were able to see both the board and the AI at the same time
    - This made values, types, etc. hard to see, as well as defocussed the participant
    - This seems to have hampered P2's chances at solving the level

## Level 4

### Phase 1
- understands and solves the simple phase

### Phase 2
- picks up on what the (-) function is from symbol
- solved phase quickly

### Phase 3
- understood (+) symbol and solved quickly
- confirms that the level is breaking down operations into its components

### Post-Level discussion
- "It started splitting the maths operations into ways to construct it from smaller bits"
    - when asked about what the level was doing


## Level 5

### Phase 1
- instantly solved phase by thinking about when exactly it was needed to be out

### Phase 2
- able to solve after some hinting about what (NEQ True) is as a boolean operator

### Phase 3
- unable to solve final phase due to how unclear mappend on either is
    - researcher demonstrated level to P2

### Post-Level discussion
- P2 guesses they would have been able to solve what mappend either was doing given enough time
    - but it would have been a trial-and-error exhaust-all-options truth table type solution
    - P2 states they would not be able to figure out what it was doing logically or through understanding
- P2 states the fork imagery for either is fine, but that linking two forks is unclear and which way it is going is just a guessing game
    - This guessing game would be hard as the values update and switch sides too quickly
        - Stepping through one evaluation step at a time like a debugger was suggested by P2 as a solution to the issue
- P2 suggests a label on each block that can be expanded into a full tutorial for that block
    - a tutorial to the level that if a user hasn't seen the concept the block is based on, they would be able to understand it's functions and use
        - for example the MAX function as an OR gate (which P2 again incorrectly identified as an AND gate)

## Level 6

### Phase 1
- instantly solved the changed left/right movement
- struggled but eventually solved using the shield at the right moment due to block placement

### Phase 2
- P2 gave up on further solving the level citing their lack of functional programming expertise needed to solve the level
- Demonstrated by Researcher

### Phase 3
- Demonstrated by Researcher

### Phase 4
- Demonstrated by Researcher

### Post-Level discussion
- Moved straight to post-study discussion as not much of the level was attempted

## Post-Study Discussion
- "It would help a lot if the functions were named"
    - "People will name them anyway in their heads, so provide that to them"
    - P2 suggests that the level designer names the functions something meaningful to lead users on the right track
    - An alternative would be a good tutorial on each block
- "The best thing is that it lets you play with it more than code does"
    - P2 likens the game to 'Baba is You', another puzzle game where you can play with things to see their effects on the path to crafting a solution. Similar to this game.
- P2 states that in its current state, the game is a teaching tool as it needs tutorial and walkthrough by a tutor
    - But in a completed state, P2 would consider this a puzzle game
- "As someone who knows very little functional programming ... \[the researchers\] explanations did a better job than \[playing\] the game"
    - "\[The game\] could be a teaching tool on its own, it just needs to be very hand-holdy"
    - P2 admits there is a lot of noise in the current state since its trying to be wide-reaching across many different things without being too deep
        - The game conveys what it is trying to do really well, but it does not achieve it in its current state
    - "You would never expect someone to learn all these concepts in 45 minutes"
        - On the short length of the study compared to what a full game play-through would be
- "I think gamifying programming is good, because \[the programmers around me\] understand how to use things, but they do not understand the concepts"
    - "People leave \[Computer Science\] degrees not knowing what they are doing, ... why they are doing \[things\]"
- P2 sees that early levels are easy to brute-force due to the low amount of inputs and outputs, which would lead to getting stuck later.
- The game gives the feeling of "oh it was super obvious, why didn't I get that earlier" when users reach the answer to the level
    - the same as most puzzle games
- P2 suggests that if the game is marketed as a way to learn haskell, the entire game has to be targeted at a very specific group
    - to the point of targeting a single year level of CS students.
- P2 suggests a text or voice based tutorial would be good
    - An 'I dont understand this' button would be absolutely needed.