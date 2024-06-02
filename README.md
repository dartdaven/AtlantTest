# AtlantTest
A test assignment from the Atlant Games studio

## Task
Create a mini-game where the goal is to collect a sufficient number of required items.

The player appears on the map at a specified point (this could be PlayerStart or a similar method).
The map consists of several rooms connected by doors.

(Implemented) The game includes an interaction mechanic: objects can be interacted with by pressing a specific key (e.g., "E").

(Implemented) A door should open when the player interacts with it.

(Implemented) Optional: Add teleport points in the game, which are paired and, when interacted with, teleport the player's character to the other point.

(Implemented) Items spawn on the map. Spawn points can be predefined, but the type of item is chosen randomly.
(Implemented) An item has a type (e.g., cube, sphere, or cylinder). When an item is interacted with, it is removed, increasing the corresponding counter of collected items (preferably displayed in the UI).

(Implemented) At the start of the game, one item type is designated as required for victory. 
(Not Implemented for Design reasons) Interaction with other item types becomes impossible.
(Implemented) All players should see the current number of collected items and the number required for victory in the UI (e.g., Cubes: 2/5).

(Implemented in debug mode) Optional: Notify other players when someone picks up an item.

(Implemented) Upon meeting the victory conditions, display the message "YOU WIN" on the screen and (Not Implemented, Restart the game instead) disconnect players after N seconds.
(Not Implemented) Optional: Allow players to exit the game voluntarily during the countdown.

(Implemented) The game session time is limited by a timer set to N seconds. If the timer ends before the victory conditions are met, display "YOU LOSE" on the screen and disconnect players after N seconds.
(Implemented) The timer should be displayed in the UI.

All code should be written with multiplayer functionality in mind. It is not necessary to make the game competitive; for instance, you can use a shared score for all players. It is important to ensure accurate display of items and data for all players.
