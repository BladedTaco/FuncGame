
## Cleaned Notes
These notes have been cleaned to be human readable rather than stream-of-consciousness get down whatever will make me remember it later.
The Raw notes (with potentially-identifying information removed) are also available. "Quoted Sections" are direct quotes from participants.

## Participant Profile

### Functional Programming Experience
- P3 has no experience with haskell
    - But has read a wikipedia page about it between recruitment and the beginning of the study
- P3 is rather experienced with other programming forms such as C++, Java, C#, HTML/CSS/JS
    - Having around 3 years of C++ experience and 5 years of Java experience

### Game Experience
- P3 is "extremely familiar with games, too familiar"
    - P3 is a Game Designer, as well as Games Programmer
- P3 is very familiar with both video games and tabletop games
    - but has more expertise in creating video games

## Level 1

### Tutorial/Demonstration

### Phase 1
- P3 Didn't recognise LT function initially, instead seeming to read the icon as piping two values into each other
    - After some hints, P3 recognised it as a LT function
- "if player needs to dodge is true, then dodge"
    - P3 was thinking in very imperative programming terms
    - This seemed to be causing some mental friction due to not being able to solve problems in the imperative way

### Phase 2
- P3 can see how the Maybe is being constructed from its inputs, how that works logically, etc.
    - This is in spite of P3 not knowing what a Maybe is

### Post-Level discussion
- Nothing of note

## Level 2
### Phase 1
- Solved quickly

### Phase 2
- P3 realised that they needed to replace the value inside the maybe, but could not figure out how to accomplish that
- After trial and error to get near to the solution, P3 was able to take the knowledge from level 1 that they needed to switch the two LT inputs since they had the opposite behaviour to what they wanted occurring

### Phase 3
- P3 given some directions to test functions with different inputs to figure out what they do, and other small hints
    - This leads to them being able to reason about what each function is doing and how to solve the phase
        - This is in contrast to the trial and error from last phase

### Phase 4
- P3 was able to use the knowledge from previous phases to solve the phase through minimal trial and error.

### Post-Level discussion
- Nothing of note


## Level 3

### Phase 1
- P3 recognised the three comparison operators (LT, EQ, MAX) as relational operators
    - After testing values, P3 was able to accurately identify what each one was specifically
    - MAX was thought to be OR as it was only tested on booleans

### Phase 2
- Solved quickly due to similarity to previous phase

### Phase 3
- "I'm starting to see the pattern"
    - "Rather than manipulating things with variables, you pass them around to functions, and chain functions until you eventually get what you want to get"
    - P3 starts to draw realizations on what functional programming as compared to imperative programming
- Working off the above basis is able to solve the phase

### Phase 4
- P3 was not able to solve this last phase before giving up due to the overabundance of new blocks all at once

### Post-Level discussion
- Nothing of note

## Level 4

### Phase 1
- Phase solved by trial and error due to small number of blocks

### Phase 2
- P3 was able to intuitively come to a solution now that they knew what phase 1 was doing

### Phase 3
- P3 instantly solved phase as they saw exactly what they have lost and what they had gained, and the connection between the two

### Post-Level discussion
- We want to "always have the same position of the attack and the player"
- "We are trying to fulfil this sign function, and we keep losing inbuilt functionality and having to recreate it"
- "That was fun ... best level ... it makes sense, making sense is what makes it fun"
    - "It's all symbols I am familiar with, which helps"
- P3 generally expressing how this level is what actually helps them learn while having fun

## Level 5
- P3 was able to determine which function was for controlling the shield from seeing the initial configuration play out
    - Likely also thanks to the iconography
- "I want to \[shield\] when I have finished moving, or when an attack is about to hit"
    - Narrows thinking down from the initial though to concrete solution

### Phase 1
- Broke the 1+1 as they saw no use for it
- P3 recognised the EQ function, and that it was always given two of the same input at the moment
- P3 reconnected 1+1 and solved the level using the absolute position, rather than the players Y position + 1
    - When questioned, P3 did not see what the difference between the two solutions is until explained

### Phase 2
- P3 started by connecting inputs up to the either block to try and figure out what it did
    - P3 was able to see its sidedness based on input order
- from there was able to solve the level with prompting about what NEQ True is

### Phase 3
- P3 was able to reason about what the chain does from iconography and type
    - "the chain links two input values, and creates a new output by linking them"
    - "it's resolving \[the inputs\] in a particular order"
    - "Resolves into a single output"
- However P3 is not able to figure out exactly how it combines the two inputs, instead relying on hints to solve the level

### Post-Level discussion
- P3 believes that they would have been able to brute force the chain function to figure out what it did eventually
    - It would take a while, "but I would eventually figure it out"
    - "when taking two values, \[the iconography of\] chaining them together gave me a really good idea of what it was doing"
    - "the symbol really helped"
    - "the split path makes sense" as well
    - "We lose the left and get the right"
- P3 and researcher agree that either mappend is unclear in haskell and because of that it is unclear in the game
    - just transferring the concept to a game does not magically make it more clear. arbitrary concepts stay arbitrary

## Level 6

### Phase 1
- Instantly connected up movement logic
- P3 then sees that the Either position is the only thing that feeds into fromEither's top input and connects it up
- When asked if there is anything different about the movement logic:
    - "\[the sign - block\] is the same, getting the relative position thing"
    - quickly followed by "no its not, its slightly different"
        - explaining how now it takes the single either rather than two positions
- "The default is don't block when there is no value"
    - On what the fromEither and EQ was doing
    - "but when there is a value; when its 1 we want to block"
    - "this overrides the default value"

### Phase 2
- Solved phase with some minor hints

### Phase 3
- P3 was able to solve the phase, but only with generous hints

### Phase 4
- P3 did not want to attempt this phase as soon as they saw all the new blocks appear at once

### Post-Level discussion
- P3 believes they would not have been able to complete the level alone, and an attempt at doing so would not be fun
    - P3 does believe they could brute force a solution, but not find one logically and would not understand their brute force solution

## Post-Study Discussion
- Had this been a full game, and this was level 20 or 30, P3 believes they would have been able to solve the level from having learnt all the constituent concepts over time, and would eventually see the level as easy.
    - "You would need time with the game prior to understand how things work"
    - "The big levels would be great about testing, but the small levels worked best as a teaching tool"
- Using Level 4 as an example of a small level:
    - level 4 worked as a teaching tool, "not because I knew the concepts, \[such as not knowing about a sign function before\], but because it was very simple, I can test what the function does, I was able to figure out what it does, and later on I didn't need to think about it because I knew it."
    - "I can link (different) functions together" such as (sign -) and (either sign) "since we broke \[sign -\] down into its components and we know what it is, therefore when the type of input changes we can think about the break down of how its working. In the same way this is feeding in the single value which is the value in the either which it operates on"
    - P3 could reason about what the either sign function does even though the inners must work differently, because the symbol is the same and the basic function seems to be the same.
- The User Experience and Game Experience made it feel easy
    - "I struggled with tasks, but I never felt frustrated, it was always simple, I could see the animation"
    - "Even if I didn't understand the concepts, It wasn't frustrating, I could try this, try that, see what happens"
    - "It's far far more bearable than a teacher telling me about functional programming"
- P3 described the current level design patterns as:
    - All components are given at the start, and the player is asked to hook them together
    - Further tests are just removing functionality or breaking it down into smaller parts
- P3 suggested instead that there is merit in doing it the other way around
    - Instead of removing functionality, add more functionality
    - Combine everything together to make simpler functions as the level progresses
    - Show the hard, low level way solved, then combine functions to get to the high level simple logic
    - this lets users understand the fundamental concepts; what each component does in isolation
    - As the level progresses, don't break functions down, just add more functions that are entirely new, and serve as an additional new task to accomplish rather than just replacing the original one.
- Level 4 is the best level and the most accessible. Because it's starting with the core components.
    - P3 suggests doing the same with the chain function, it would teach them what the chain is doing much better and in an easier way.
        - Don't introduce chain mid level, introduce it in its own level first.
- I like to see how the underlying function is working, but you are just breaking functions down and I don't know what these individual parts do even if I know what the combination of them was achieving.
- Start in isolation with the small components, and make sure the player understands exactly what those small components are doing
    - The researcher shared the design docs of the unimplemented class tree system, and P3 agreed it does exactly this
- P3 talks about recently they have been trying to avoid tutorials for writing code, and instead trying to understand exactly what they are doing.
    - P3 likens this to the game in that they can learn to do things through repetition, but that doesn't necessarily mean they understand what they are doing.
    - They are solving through pattern recognition rather than fundamental understanding.
- The concept for the game is good, but the implementation falls short.
    - It is on the right track, but it needs to be iterated on and expanded.

- P3 affirms that the concepts from games they recognised transferred over well to this game
    - They understood health, mana, stamina (status bars)
    - They understand left/right movement (shielder movement)
    - They understand this set of nodes controls movement, and this set of nodes controls the shield (parallel control flow level)
- Breaking components down doesn't let the player recreate the functionality of the larger function if they haven't been introduced to the smaller functions
    - Its teaching too late; teaching as they need to use it in a test
- Learn in isolation, so that later when its testing/learning in context, I do not have to worry about too many things.

- "\[The game\] was really fun, it was really good"
- "Implemented correctly it would be a great teaching tool, and it would be amazing for creating interest."
- "Its \[also\] accessible. I learnt more than if I had read a textbook"
- "It makes me want to go and look up functional programming paradigms and learn more about it; see where it might be applicable to my own programming and future projects."

- "The game element makes things happen, so you have instant feedback"
- "In playing a game, you go up against a challenge, and you get small challenges followed by rewards from beating it."
- "A relative who knows no programming could still enjoy this game I think. It's simple in concept, but can teach complex concepts."

- "As someone who makes games and who programs, it makes me feel the joys from both"
    - The game is "really cool conceptually"
    - "It really comes across in this game design \[the designers\] tendency to want to solve big complex challenges rather than many quick small ones."
- "Its really satisfying to snap the nodes together"
    - "I really enjoy not having to write textual code"

