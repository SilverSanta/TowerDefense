# INSTRUCTION
The zipped file contained within this repository needs to be unpacked directly in the main folder for the project to work.

# TowerDefense
This is a tower defense game, where th player needs to set traps and cast spells to prevent enemy units from reaching and destroying the base.

Player input:
- Mouse is for selecting traps/spells and placing them on the map,
- Camera movement is supplied by arrow keys and via dragging with mouse (holding LMB and moving the mouse),
- ESC is used to escape to main menu or to stop placing objects.


Issues:
- pathfinding can crash the game if the path to the base is blocked for the enemies. Therefore -> it is highly advised not to block the path entirely (the passage can be blocked, however, if the enemies can go around towards the base).
- Memory leakage (mmemory is not released when deleting object). Should not be a problem if the player does not restart the game multiple times without exiting it).
 
