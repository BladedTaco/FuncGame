## Cleaned Notes
These notes have been cleaned to be human readable rather than stream-of-consciousness get down whatever will make me remember it later.
The Raw notes (with potentially-identifying information removed) are also available. "Quoted Sections" are direct quotes from participants.

## Participant Profile
### Functional Programming Experience
- Has used Haskell before
- Has not used recently, and does not remember a lot of it

### Game Experience
- Participant is very experienced with games, mainly video, but also tabletop.


## Level 1
### Tutorial/Demonstration
- "The gameplay seems simple enough."
    - After Demonstration
- "It will take some time to understand what everything does."
    - While learning the controls

### Phase 1
- P1 first went through all the controls demonstrated and confirmed they understood how they worked.
- P1 then started solving the level, initially connecting LT block the wrong way around as was done later in the demonstration, but then looked at the game board and realised that it needed to be switched.
- P1 Solved Phase: Minimal Difficulty

### Phase 2
- "It has to be unlocked before I can hook it up"
    - On seeing the Maybe/Mimic Function and seeing that it doesn't connect anywhere without inputs
- Connected valid input to Maybe function 
- "is that just adding 2?"
    - On mistaking the LT block as add, this mistake seems to have been made due to the overly fast speed at which the inputs update, making it hard to see values as groups. May also suggest unclear iconography.
- On prompting to look at the inputs/outputs again, realised the 'add' block was a LT block
- P1 solved Phase: Low Difficulty, Unclear functions

### Post-Level discussion
- P1 instantly recognised the Mimic as a Maybe as "It's either something or nothing"
- P1 recognised the Dice/Int as a numeric value
- P1 recognised the Coin/Bool controlled whether the Maybe was Just a / Nothing.
    - Thought the coin was Just / Nothing rather than a bool.
- P1 recongised the LT function as Comparison
    - says star points to the bottom input as what is important
    - says but both are equally important as its some comparison
    - Is unsure exactly what comparison it is, but recognises it as a comparison
    -After being told its a LT block, P1 confirms that makes sense and its comparing against the bottom one, but wouldn't have figured that out working backwards from the inputs/outputs.


## Level 2
- Before beginning, pointed out the returning LT function
    - After beginning confirmed this by checking inputs/outputs with values
### Phase 1
- Sees Hide as some sort of Teleport
    - This is due to the misleading visual of gong to bottom left corner
    - But also works thematically as a solution to the same problem
- Recognised the LT ordering issue again, and fixed it.

### Phase 2
- Recognises the Just 0 block first as a Maybe, then sees its always 0 as the inner input has been taken away.
- Hooks up position to LT as a way to test different values using constants
    - continues to hook it up to different things to see the effects
    - From this exploration, pieces together the solution as most functions are already connected due to the exploration
- Realises we need to "set the Thieves position" away from the X's
    - Realises the Maybe is needed to do this
    - Realises the Maybe can't output 0,0 as that would kill Thief
- Reasses the situation, walking through each block and what it does, and what is missing
- Tests inputs on the const function to figure out what it does
    - After a while asks for hint and is told what the function does
- Connects maybe to fmap as the only valid input for Functor a and sees the type signature narrowing
    - from there sees how to use the const function and replace the value in the maybe with it
- P1 recognised it starts the same as the previous level
- Knowing how the last level was solved "does help in that I know what I did to solve the last level" and that puts me "on the path to solve this one"
    - "I need to teleport in and out, and not be in the red X's" at X/Y=0
- Was not sure what const was from the symbology or the inputs/outputs
    - This suggests either the symbology is unclear, or it is not an easy concept in visual languages
- After knowing what const does, P1 was able to reason about how it could have been used to replace the value in the Mimic when treating the Mimic as a Flask Input
    - Does not connect this to Functor, but does see how it is once told
    - from there recognises the flask block as fmap

### Phase 3
- P1 recognises the difference for this phase is the triple flask being given instead of the single flask
- P1 get part of the solution by putting the const function inside maybe, but thinks this is a mistake and not helpful in solving the level and undoes this
- P1 questions what is different about the triple flask compared to the single flask
    - Does this suggest the type signature isn't visually distinct enough? Or some animated form of replacement is needed?
- Once connecting the Just 0 to the Apply bottom output, saw the type signature wanted a function in a chest for the top input
- P1 reconnected const to the Just constructor and solved the phase

### Phase 4
- Recognises that liftA2 is the main function this time around, and that it wants a function that takes two inputs and returns a single value
    - quickly connects up the available chests to liftA2, sees that const fits the top type signature, and solves the level

### Post-Level discussion
- When asked about what the liftA2 block was doing different to Apply block 
    - liftA2 and Apply are related as liftA2 has 3 inputs while Apply has 2 inputs
    - liftA2 combines the two inputs together using the given function, while Apply has a function in one mimic already
    - liftA2 and Apply are very similar and are conditional in some way
        - One input as a condition input
        - if one input is bad (Nothing), then it wont output anything
        - (Both are 'conditional inputs', but only one is ever used as such in this level, leading to the confusion)
- Can now reason about the key metaphor for functions and how its being used to unlock values

## Level 3
- Recognises the addition in this level where there is the moving row of crosses that needs to be avoided in combination with the previous attacks
    - Guesses and confirms that the X position of the column is given from the X function block
    - States that this function is useful to know when to dodge, and that it needs to be combined with the old logic
### Phase 1
- Now that LT EQ and MAX are all next to each other, P1 understands what each comparison is from its icon
    - Struggles a bit with MAX, but once different inputs are connected up is able to solve what it is
    - Switching from connecting ints to MAX to bools, and sees that MAX works as an OR for two booleans.
- From there makes the last connection to solve the level quickly

### Phase 2
- Sees how some inputs/outputs have turned into maybes
    - "Its an equals" function "still, but now it has a chest" input
    - "Max is the same"
- quickly connects the closest maybe available to each maybe input to solve the phase

### Phase 3
- Plays around with the Bind function to figure out what it does
    - Quickly realized its a "chain function" from the icon
    - Guesses that its related to bind or monads
- Understood quickly what the level wanted with the position becoming a maybe and the bind accepting a maybe

### Phase 4
- Participant was offered to skip this phase as they felt overwhelmed with all the new functions
    - They accepted this
- "I need to play more puzzle games obviously"
    - In response to having to skip the phase.

### Post-Level discussion
- "I see this as a game. I don't see this as a tutorial"
    - when questioned if they felt at all like this was a tutorial or teaching thing

## Level 4
- "I need to be in the same row, the column does not matter"
    - Instantly realising the goal of the level when first seeing the board
### Phase 1
- Sees that (sign -) outputs the difference between the two inputs, and that the shielder doesn't move the correct direction
- Quickly flips the inputs around and solves the phase

### Phase 2
- Recognised that the level was breaking the (sign -) into two more low level functions which compose to make (sign -)
- Connects up the inputs correctly instantly, only needing to flip inputs again

### Phase 3
- Sees (-) break into (unary -) and (+) and sees how the (-) function can be replaced with these functions
- "The maths ones are so easy, I love maths"
    - Upon solving the level extremely rapidly

### Post-Level discussion
- "I was invested in the level"
    - Recognises that they would have enjoyed the earlier levels just as much, had there been a lead-up of smaller,easier levels before those big challenging levels
    - "It was fun because I knew how to solve it"
    - "Completing levels ... accomplishment is fun"


## Level 5
- "I can see the yellow bar going down and I can tell that's bad"
    - Realising the goal of the level, and seeing that the shield drains stamina

### Phase 1
- recognises 1+1 == 2, and 2 == 2 so it will hold shield forever
    - This is what needs to be fixed
- Solves phase quickly by using the attacks y position, but does not use shielder y position

### Phase 2
- "This is a NEQ"
    - upon seeing the new functions, was able to recognise from icon
- This is a fork block, and this block takes a fork so these must connect together
- Recognises that NEQ True is a NOT operator after some prompting about why True is given with NEQ.
- Connected up inputs to the Either constructor, with the two bools switched
    - Figured out the mistake when the shield was disappearing exactly when it was meant to block
- Was not able to reason about what the two bools were doing in the Either constructor until some prompting to zoom in

### Phase 3
- "I've lost the fork, and its split into two"
    - and been given "another function" which "must connect the two somehow"
- Connected the two eithers the wrong way around
    - This caused the shielder to move when it was meant to shield
    - "I can tell this is near what I want, but slightly wrong"
- After some prompting fixed the issue

### Post-Level discussion
- P1 doesn't understand the metaphor, as chaining forks doesn't make sense
    - this suggests that the mappend metaphor is clear, but now how either's are semigroups
- "this is teaching if and else ... control flow"
    - On asked what the shielder was about

## Level 6
### Phase 1
- P1 connects up the position controlling functions instantly
- Then connects the Either to the fromRight as nothing else can go into it.

### Phase 2
- After some failed attempts, the participant gives up on the level as they feel out of their depth
- Not completed, but is demonstrated by Researcher

### Phase 3
- Not attempted, but is demonstrated by Researcher

### Phase 4
- Not attempted, but is demonstrated by Researcher

### Post-Level discussion
- P1 think they would have been able to solve the level, but not within a reasonable amount of time, or had fun doing it
    - "30 minutes to an hour I could solve this" level


## Post-Study Discussion
- Total time taken for the study was over 2 hours
    - This may be due to a lack of experience with haskell, but future participants will clarify this point
- User Interface and Controls
    - "Middle click to pan is confusing at first, but learnable"
    - "Same with right click to drag blocks around"