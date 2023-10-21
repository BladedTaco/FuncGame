
## Cleaned Notes
These notes have been cleaned to be human readable rather than stream-of-consciousness get down whatever will make me remember it later.
The Raw notes (with potentially-identifying information removed) are also available. "Quoted Sections" are direct quotes from participants.

## Participant Profile

### Functional Programming Experience
- Has half a year of haskell programming experience

### Game Experience
- Has a lot of experience with games
    - Equally has a lot of experience with video games and tabletop games


## Level 1

### Tutorial/Demonstration

### Phase 1
- Solves level as shown without error or delay

### Phase 2
- Solves second phase in the same way, even picking up to switch the LT inputs before looking at the board.

### Post-Level discussion
- Nothing of note


## Level 2

### Phase 1
- Phase solved quickly due to similarity to last level

### Phase 2
- P6 connected different inputs into the const to try to figure out what it does
- P6 is able to figure out the const should connect to the fmap as it matched purpose and type signature
- P6 then connects up the maybe and solves the phase

### Phase 3
- P6 notices the difference between fmap and apply, and quickly solves the phase by satisfying type signature

### Phase 4
- "I could connect \[position input\] directly (to position output), but that wouldn't help as then I stay still"
    - When trying to figure out what needs to be done with the new maybe position input
        - As now there could be a direct connection, even if it is not the level solution
- P6 sees how liftA2 seems to be applying a function across two wrappers
    - P6 is then able to reason about how const is needed without partial application to have a 2 input function
- P6 solves the level rather quickly

### Post-Level discussion
- Nothing of note


## Level 3

### Phase 1
- P6 is able to recognise LT, EQ, MAX from a combination of iconography and value testing
    - Sees MAX as OR due to testing on bools
    - P6 complains that its hard to tell from the values alone as they update too quickly
- "Its an OR because its dodging" both attacks
    - When questioned about why they think its an OR block and what its doing.

### Phase 2
- P6 was able to recognise the difference in that some inputs became maybes and made the correct connections
- "We are running the comparison as a function this time"
    - As compared to a base comparison, now it has extra logic around it

### Phase 3
- P6 was able to reason about how bind and the maybe EQ work together to compare two maybes rather than a maybe and an int

### Phase 4
- P6 was able to find a lot of functions that have inputs with matching symbols to only a single meaningful output.
- P6 struggles a bit due to thinking that all blocks need to be used, and cannot find the canonical solution which uses the maybe constructor
- Once told that not all blocks have to be used, P6 was able to solve the level with the easier solution.

### Post-Level discussion
- Nothing of note


## Level 4

### Phase 1
- P6 initially tries to solve the level using the Y-positions
    - But is able to realize that the X-positions are what will solve the phase
- P6 quickly realizes that the position inputs need to be switched around as the shielder moves the wrong way.

### Phase 2
- P6 exclaims "\[they\] see what to do" instantly upon seeing the two new blocks
    - P6 demonstrates this by instantly connecting up the inputs correctly.

### Phase 3
- P6 sees that the only function with two inputs is the plus, and so that is the combining step in adding two values
- P6 struggles a bit to realise the (unary -) needs to be on the input of (+) rather than output
- After realising this, P6 then struggles with the commutativity of (+), switching the inputs around rather than switching which one is connected to the (unary -) function.

### Post-Level discussion
- Nothing of Note


## Level 5

### Phase 1
- P6 realizes the shield is always out, and this is what needs to be changed
- Once realising that the Y positions are important now rather than X positions, P6 solves level quickly

### Phase 2
- P6 was able to solve the phase just from being told how NEQ True can be used as a NOT.

### Phase 3
- "We split the one 3 input function into the two constructors, then combine them"
    - P6 after some prompting about what changed and how we can replace the missing block
- Was able to solve the level by swapping around the mappend inputs after seeing the board wasn't acting as expected

### Post-Level discussion
- Nothing of note


## Level 6

### Phase 1
- P6 was able to quickly solve the first phase
- When asked, P6 was able to explain what fromRight is doing and how it is getting a value out of the either

### Phase 2
- P6 understands that the way to get a value out of an either was lost, and so the 2 new blocks must also be able to do that.
- "We are using the key as a function again ... and I can see how that gets the value out of the fork"
    - When asked about how the new blocks replace the old function

### Phase 3
- P6 was able to solve phase about some prompting on what the chain block does and what needs to be fed into it

### Phase 4
- P6 saw the flipping functions from the type signatures
- P6 recognises that GT 0 can be used to convert from difference in x position to boolean side
- P6 was able to solve the phase with some prompting about what needs to be replaced
- We are "replacing the left/right boolean by calculating it" from the integer difference in x position
- As part of that, we are "flipping around \[the either\] to operate on the right" value

### Post-Level discussion
- Nothing of note

## Post-Study Discussion
- "Since I had some functional programming experience, I recognised some of the concepts in the blocks"
    - "Functions inside functions" (currying)
    - "levels of functions, taking things out of boxes" and having values with different nesting levels
- "Chucking a novice programmer straight into the last level would make them quite programming"
- "The symbols didn't make sense to me without further explanation"
- "More explanation and showcasing of what each function does would be good"
- P6 recognised "levels were generally about one concept", where "later levels leveraged earlier levels concepts and introduced one new thing to spice it up"
- "If it was a fully polished game I would give it a go, but I am unsure if I would play for long"
    - P6 states if they were told in addition to being a game it also teaches Functional Programming, that would detract from how likely they are to play the game.
- When asked about if the found the game fun
    - "It mimicked to an extent real programming where completion is rewarding, and seeing how different things connect is fun"
    - "It was more fun than programming, and was fun at points"
    - P6 suggests a hint system would make it a lot more fun and reduce frustration.
- When asked about the best level
    - "Level 3 was the most interesting, because there were two things I had to account for rather than just one"
    - The level had "two adjacent but connected issues. \[where\] solving one issue helps with solving another issue"
    - It also "transitions really well from the previous levels in combining two concepts I learned from the previous levels"
- When asked about the worst level
    - "The last level was far to complex"
    - "If there was a more gradual transition I would have enjoyed it more"
        - i.e. in the context of a full game where it is level 40 instead of 6.
- "If it used all 3 teammates AIs it would have been more interesting having 3 small problems across the 3 AIs" as well as having interactions between their AIs.
    - "Having big functions isn't fun, having a lot of really small functions would make it more enjoyable"
    - "Being able to control all 3 characters would be really fun if it was able to have more restrictions on function placement"
        - P6 is suggesting that the number of things to consider should still be kept small, and if functions are placed suggestive towards a solution, they should be stuck there
    - "The main function was making the functions was a valid output" but P6 suggests instead "if functions give valid outputs and its not productive to the boss fight"
        - P6 is suggesting that trial and error, or just working off types shouldn't be enough to solve a level. Understanding should be needed.
        - P6 suggests there should be more blocks than is needed to solve the level, with multiple options for solving the level and some red herrings.
        - This would add more game complexity without adding more functional programming complexity
        - This type of design allows for "open problems rather than a closed golden path" through the level
        - P6 suggests this to "make the gameplay ... more enjoyable" rather than increasing "the functional programming aspects"
            - Fun rather than teaching tool
    - "Multiple agents moving around would be fun"
        - P6 also suggests puzzles based on positioning the units correctly rather than solving other complex actions.
    - P6 suggests using "Small, easy to understand things, trick \[the player\] into learning" rather than making it obvious they are learning.

