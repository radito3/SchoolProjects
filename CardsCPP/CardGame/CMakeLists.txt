cmake_minimum_required(VERSION 3.9)
project(CardGame)

set(CMAKE_CXX_STANDARD 11)

add_executable(CardGame main.cpp Card.hh Command.hh Commands/TopCard.hh Hand.hh Deck.hh GameError.hh Commands/BottomCard.hh Commands/DrawBottomCard.hh War.hh Belote.hh Santase.hh Commands/DrawTopCard.hh Commands/IsBelote.hh Commands/Shuffle.hh Commands/Sort.hh Commands/Deal.hh Commands/Remaining.hh Commands/Highest.hh Commands/PlayCard.hh Commands/Size.hh Game.h GameFactory.h Game.cpp Belote.cpp Santase.cpp Commands/IsTierce.h Commands.h Commands/IsQuarte.h Commands/IsQuint.h Commands/HighestOfSuit.h Commands/IsTwenty.h Commands/IsFourty.h Card.cpp)