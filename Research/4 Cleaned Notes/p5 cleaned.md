
## Cleaned Notes
These notes have been cleaned to be human readable rather than stream-of-consciousness get down whatever will make me remember it later.
The Raw notes (with potentially-identifying information removed) are also available. "Quoted Sections" are direct quotes from participants.

## Participant Profile

### Functional Programming Experience
- Quite inexperienced and rusty with Haskell
- Familiar with Functional concepts from maths.
- "Outside of a maybe, I don't know much about haskell in general, I only remember the rudimentary stuff."

### Game Experience
- Extremely familiar with both video games and tabletop games.
    - Both in design and playing them.
- "Tabletop games I have played less, but know how engines are constructed and how they are played and work."


## Level 1

### Tutorial/Demonstration

### Phase 1
- P5 connected up the block instantly as was demonstrated
- P5 talking aloud on what the program was doing identified LT correctly from icon and function.

### Phase 2
- P5 again quickly solved the level as demonstrated, and upon seeing the board realized the need to swap the two inputs to LT.

### Post-Level discussion
- Nothing of Note


## Level 2

### Phase 1
- Solved instantly

### Phase 2
- P5 quickly identified Mimic as a maybe
    - from there was able to work out that const of fmap puts a function inside of a maybe
- P5 struggled with identifying that the value in the maybe needed to be replaced.
    - P5 eventually stumbled onto a solution but was not able to explain what they were doing.

### Phase 3
- P5 solved the level through looking at the type signature of apply

### Phase 4
- P5 recognised the imagery of the liftA2 flasks where its providing two keys to unlock a functions value in a context.
    - This imagery recognition helped in solving the level

### Post-Level discussion
- P5 was able to recognise the level was about maybes, but was not able to recognise the const function


## Level 3
- P5 recognises the LT, EQ, and MAX functions look like comparison functions from the iconography

### Phase 1
- P5 is able to identify LT, EQ, and OR as the comparison functions by feeding values into them
- P5 noted this was a bit of a struggle due to how quickly the values changed.
- P5 was able to solve what each block could do on its own, and then connect those functions together to solve the phase

### Phase 2
- No problems encountered reconnecting the inputs

### Phase 3
- P5 instantly recognised how the type signature of bind could be satisfied and used towards solving the level
    - From there P5 solved the phase

### Phase 4
- P5 breaks down what they need to do to solve this level, and reasons that the final function must be MAX to combine the two logic streams.
- Works backwards from the MAX to figure out the function of each block one by one to solve the level logically.
- P5 was not able to figure out what fromMaybe did, but was able to figure out how to use it from connecting the types
    - P5 was able to understand what the function was doing after a brief explanation and reasoned about how it was being used to solve the level

### Post-Level discussion
- P5 recognises that binds icon shows mixing the values inside the second flask, and from there is able to reason about what the flask metaphor is in terms of functional concepts.


## Level 4
- P5 was able to guess at the goal of the shielder in the level only from seeing the visual, before any explanation was given.

### Phase 1
- P5 connects the nearest inputs instantly, and sees the need to switch the sides around when looking at the board.

### Phase 2
- P5 is able to solve this phase similarly quickly once they see sign has been reduced to one input and the subtract has two.

### Phase 3
- P5 solved this phase quickly as well, but ran into some trouble figuring out if they wanted to do + or - first.
    - After thinking on it some more they solved the level instantly.

### Post-Level discussion
- "The level was literally mathematical functions being applied in certain orders"
    - On what the level was doing
- There was "no actual mathematical difference when the function is broken into its components"
    - Mentions simplification of equations
- "The mathematical stuff makes a lot more sense than the non-mathematical stuff"


## Level 5

### Phase 1
- P5 was able to solve the level quickly
    - P5 identified both the easy (1+1) way and canonical (Y+1) way of solving the level
- P5 was able to recognise NEQ from the icon.

### Phase 2
- P5 connected up inputs to the either until the output type looked correct
    - This was enough to solve the level.

### Phase 3
- P5 was able to figure out what the chain block outputted, but could not reason about why or how it was getting there.
- P5 agrees with consensus that "chaining together two eithers is hard to understand"
    - P5 says they only solved it though looking at the values rather than understanding what it did

### Post-Level discussion
- Nothing of note

## Level 6

### Phase 1
- P5 quickly solved first phase as they were able to see the world input block was a delta position

### Phase 2
- P5 needed a reminder on what const did, but once reminded was able to reason about how it could be used with foldr to get a value out of a context by looking at the type signatures.

### Phase 3
- P5 initially connected blocks together where movement worked correctly but shielding always happened when movement wasn't happening.
- P5 solved this level with a solution that blocked more often than required, but still blocked rarely enough that the lax constraints on the level meant it was a much simpler solution that passed the test than the solution which only blocks when needed.
    - This solution did not use fmap

### Phase 4
- P5 wanted to solve the final phase specifically due to being told it was hard enough that no previous participant had solved it.
- Due to the easier solution last phase P5 did not initially see the use for fmap which was not used last phase.
- After some hints about what fmap could be used for, and what the either flip functions did for either as a flask, P5 was able to solve the level.
    - P5 struggled with the concept of flipping eithers to work on the originally left value while its on the right, and then flipping back to have the type needed by other functions.

### Post-Level discussion
- Skipped in favour of moving straight to post-study discussion

## Post-Study Discussion
- the game "needs more explanation of components, rather than making it a mystery"
- "There was low friction between the concepts that I understand \[and how they were presented to me\], but I am going in a little bit blind" (due to rusty haskell experience).
- P5 struggled to see much linking concepts from games, but suggested it "may be a UI thing"
- P5 affirmed that "this method of teaching is good for teaching to novices in general if they start with this game and then move into haskell as they will be able to apply what they learnt"
- P5 suggests that its "quite hard to go from haskell to the game" as while you "learn the concepts intuitively quite well" the preconceptions that haskell experience brings change the users view of the game.
- "As a full game, I would want syntax highlighting, hinting, and other programming language features"
    - This was suggested as both extending existing features like the type match highlighting, but also as new features as well.
- "Its quite good in execution and how it is to use experientially"
- "a novice programmer would absolutely be able to solve these questions if they have a mind for it"
    - as the game progresses "at a good pace, but not too fast"
- "\[About\] the tasks; I knew what I wanted to do, but I wasn't sure how to set up the particular things"
- The "UI was great"
- "I expected tasks to take longer \[than they actually did\], and fiddling around with a stochastic approach took less time \[than solving some levels logically\]"
- P5 did not find the game frustrating at all, "but that may be due to being a patient person"
- P5 suggests making it more game-y, increasing physical interactivity in the 3D space, or providing more information to the player.
- P5 criticises that "the icons that are being used could be any icon personally, random letters would have been just as good"
    - "the chest however was a great transferable concept, and I was able to understand it as soon as I thought about what it might be."

- P5 found the two best levels were:
    - Level 4 as there was the most instant grasp and understanding of what the level was doing and how to solve it.
    - Level 6 was the best overall as they found the unexpected simpler solution that was more intuitive to them than the canonical solution.
        - P5 really enjoys finding alternative solutions to puzzles, especially beating dev times in games.
- P5 also enjoyed Level 3 as they solved it much faster than the supervisor was expecting.

- P5 recognised that each level had one main concept associated with it
    - P5 was able to identify the concept for levels 1 2 3 and 4.
    - P5 was unable to identify the concept for levels 5 and 6 due to not having a grounding in what functional programming concepts they were tackling.
        - Unfamiliarity stopped a connection from being made.
- P5 was able to recognise the classes also had an associated concept.
    - "The thief was about changing position and nothing else"
        - Once asked if they saw a connection between the thief and chests, P5 said that it was really obvious in retrospect since thieves and chests are normally hand in hand.
    - The shielder was "not only about changing position, but also changing something else simultaneously"
        - As a programming concept: logic or control flow.
        - P5 can reason about what type of control flow each level is about after some slight prompting.
- "If this was a full game, I would play it independently with better presentation" or obfuscated presentation.
    - "Put down in front of \[the game\] I would sit down and play it"
    - "if I was told it also teaches functional programming, I would love to play it more"
        - i.e. its an interesting game on its own right, but knowing that it teaches functional programming would motivate P5 to play it more on top of the game aspects.

- P5 found Level 2 their least favourite
    - they chalk it up to still being confused about what the game is and having to learn how to play it.
    - P5 suggests players really need to be eased into the game smoothly.
        - "Had the game started with Level 4 as my first independent level it would have been a far better introduction."
