
## Cleaned Notes
These notes have been cleaned to be human readable rather than stream-of-consciousness get down whatever will make me remember it later.
The Raw notes (with potentially-identifying information removed) are also available. "Quoted Sections" are direct quotes from participants.

## Participant Profile

### Functional Programming Experience
- Has some haskell experience, but not a lot
- Very familiar with Rust and its functional paradigms

### Game Experience
- very familiar with video games
- less familiar with tabletop games

## Level 1

### Tutorial/Demonstration

### Phase 1
- "the time based thing seems to be a random seed"
    - P4 confusing the attack countdown as some random number
- "The dice is a constant 2"
- "This function seem to be a comparator ... LTE"
- P4 recognises the tick and cross type as a bool
- "these left \[functions\] come from the world, so we can use these to update the state"
- "that makes sense"
    - On solving phase and seeing solution working

### Phase 2
- Recognised Mimic as a Mimic; Showing the Mimic Icon is readable
- "So we want to update its position"
- P4 figures out the control flow for the phase, but hasn't made the LT input flip
- "Lets go through the control flow and see what is happening"
    - In doing this corrects themself saying it is a LT block rather than a LTE
    - Sees that for the position output, "when it is a non-question mark it warps out" (backwards)
- flips around the LT inputs and solves level

### Post-Level discussion
- P4 had no idea that the clock was a countdown to the next attack, and thought it was just a random seed
    - Once it was explained as an attack countdown, P4 was able to reason about how it was being used to solve the level
- P4 saw Mimic as an Optional<T> from Rust, which is the Rust equivalent of Haskell's Maybe a
    - From this was able to reason about how the Mimic constructor worked in terms of Optional
    - From this was able to reason that it was actually when position was unknown is when the thief was jumping off the board


## Level 2

### Phase 1
- Recognises from last level that the clock is countdown to attack
- Solves phase instantly as it is repeat of last level

### Phase 2
- P4 was unsure about what the flask function did until a mimic was connected as the bottom input
    - The narrowed type signature helped P4 understand what the function wanted
- P4 struggled a bit with currying / partial application on the const, but once they figured it out they were able to solve the level logically
    - P4 saw how composition was being used to replace the value inside the Mimic    

### Phase 3
- P4 recognised that the new 3 flask function needed a function inside a mimic
    - P4 was able to satisfy this quickly and solve the phase

### Phase 4
- P4 sees that liftA2 allows for two flask data types with different inner value types
- P4 can reason about how const can be used across these two values to combine them into a new Mimic
- However P4 still struggled on how that all fits together to solve the phase

### Post-Level discussion
- P4 didn't really understand liftA2
    - "I think its composing something, but I'm not sure what"
- Once the demonstrator showed the three flask blocks side by side:
    - P4 was able to see the progression of how it changes; Where the function is in relation to the context(s)


## Level 3
- "I wonder what this door icon is"
    - Shows interest in new icons
    - This was clarified to be a mirror as icon clarity testing was not part of the study's goals, but rather testing of the concept of the icon

### Phase 1
- P4 took some time to understand why all the different comparison operators were needed
    - When questioned on what each comparison was P4 was able to answer correctly from iconography

### Phase 2
- "Maybe comparator? Some sort of optional operator"
    - P4 was able to recognise this phase introduced maybes to the comparison inputs
- P4 was able to quickly solve this phase

### Phase 3
- P4 recognised that bind is "composing something"
    - Clarifies to: "using partially applied functions to compose with a concrete value to return an unwrapped value"

### Phase 4
- P4 solved the phase quickly and without mistake

### Post-Level discussion
- Nothing of note


## Level 4

### Phase 1
- "I'm gonna check what this does with my own eyes"
- works it out through trial and error of what (sign -) does, then works it out logically what the level wants them to do with the block.

### Phase 2
- P4 sees what has happened, and sees the solution to the level
    - However they first test to see what happens without the sign function
        - Which is that overly large values are ignored
- P4 then solves the phase after completing their experiment

### Phase 3
- P4 connects an input to (unary -) and sees what it is doing
- From there P4 logically solves (a - b) as (a + -b) quickly

### Post-Level discussion
- "this level has intuitive operators in how they work, and its easy to test their inputs/outputs to see their effects."
- P4 understands this level is about splitting functions into their components
- The first time it was just -1 0 1 as outputs, but then we had to start piping things together to get the correct values.


## Level 5

### Phase 1
- "always having the shield out depletes stamina, so I don't want that"
    - P4 figuring out the level goal from seeing the board
- "its like before, where we want the position of the x thing"
    - P4 figuring out the level solution
- Phase was solved instantly
    
### Phase 2
- P4 zoomed into Either to see the Any colours matching up to see what inputs it wanted.
    - P4 matched this with the Either in the output function to solve the phase quickly
- "the either is returning the one that has a defined value"
    - On the function of Either constructor

### Phase 3
- P4 figured out that this phase gave a Left and Right constructor, and the chain could be used to connect them
    - But was not able to figure out what connecting them meant logically or in terms of the solution
- Researcher told P4 what mappend did for two Eithers, and from there P4 was able to solve the level

### Post-Level discussion
- "eventually I would have found out what chain was doing, but it would have taken forever, and is not clear"
    - On the unclearness of mappend for Eithers


## Level 6

### Phase 1
- P4 solved phase easily

### Phase 2
- P4 had some issues around functions appearing as if they could not connect together when normally they could
    - for example P4 connected up an input to const, partially applying it, and then couldn't find a function to feed into foldr
        - A few hints from the researcher solved this issue

### Phase 3
- "The flask is used to get a 1 or question mark"
    - P4 figuring out what the fmap block is used for in this phase
- "The comparison is used to get a bool out of the either based on when its 1"
    - P4 figuring out how to get a bool out of two eithers using the EQ block

### Phase 4
- P4 did not attempt to solve the final phase
    - "the last phase looks really complicated, I would have eventually solved it by the left right thing, but it would have taken forever"

### Post-Level discussion

## Post-Study Discussion
- P4 found that they needed to warm up their functional knowledge towards the start
    - But once it was warmed up, they were able to relate things in the game to rust concepts
- P4 found the symbols confusing
    - "It adds an extra layer of trying to figure out what the symbol is, they often needed explaining"
- P4 thinks that as an introduction to Functional Programming, it needs more guidance on what specific things each function block is doing
- P4 suggests having more 'understandable' levels like level 4
    - "I can figure out whats happening, and it doesn't feel functional programming inspired"
- P4 found the currying and partial application "does make sense when you get used to it, but \[they\] got too focussed down on the key and lock stuff"
    - They eventually figured out the key and lock analogy for functions, but it took them quite a few levels to figure that out initially.
- "With levels in between the levels presented, I would be able to figure out the more difficult levels by myself" from leading up to the complex things with many simpler things
- "Level 2 with flask and lock and key was too much to take in at once", P4 instead suggests "introduce one concept at a time"
- "I was able to make connections to the rust concepts once I figured out the option type"
    - "once I figured out what the key and lock did as a partial function, I figured out the maybe"
    - "I needed a foothold to go off so I could have a function that is half understood, so I can infer the rest and test to find out if its what I think it is"
- P4 could recognise concepts that had been brought over from games
    - "The block connections reminds me of a game where I connected tiles together"
    - "A mimic is a maybe, because a chest usually contains something, but sometimes it doesn't"
    - P4 solved the d20 as Int, but the coin flip as bool was a bit too generic to belong to anything, it was a just a true/false
- "The difference contexts was cool; having thief vs having shielder to explore different concepts was interesting"
    - P4 identified thief is about movement and maybes. 
        - P4 also understood how Level 3 was about Monads
    - P4 saw the shielder was about moving and using its shield; Moving and defending. 
        - Identified Level 5 as being about parallel control flow
        - Identified Level 4 as being about synchronous or sequential control flow
        - Identified Level 6 as using either as a form of control flow
- "the game was fun, it was interesting to think about what things did"
- "its more of a teaching tool right now, but it could be turned into a full game when finished"
- P4 identified that in parts the value updating happened too fast to understand what some functions such as the comparisons do.
- P4 affirms They'd "be motivated to play this as a game if it was finished I wouldn't need to be forced" to use it as a teaching tool for learning, but rather be able to play it as a game for fun.