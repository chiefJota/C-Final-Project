# Camping Survival
## To-Do List
* [x] drawSquare method in graphics_starter (Takes color and position)
	* [x] drawPlayer method in graphics_starter (Takes color and position. Has 'arms'.)
* [x] Instantiate the Player and Tent objects in graphics_starter init method
* [x] Instantiate the Items Vector in graphics_starter init method
* [ ] Logic to find when a new day starts
	* [ ] Generate item objects at random locations
	* [ ] Add generated items to Items Vector
* [ ] Draw Player, Tent, and all Items in the Items Vector using drawPlayer and drawSquare respectively
* [x] Allow player to move
* [ ] Add game states
	* [ ] Instantiate current state in graphics_starter init method
	* [ ] Add start screen
	* [ ] Add death screen

## Git with a Group Commands
To be used after you link your local repo to the project on GitLab.
* git pull origin master
* git checkout -b [YOUR_INITIALS]_[WORK_DESIGNATION]
* Do work. Check to see if it works.
* git add -A
* git commit -m "[COMMIT_MESSAGE]"
* git push origin [YOUR_INITIALS]_[WORK_DESIGNATION]
* On GitLab, send a merge request for your branch
* Wait for code approval.
* git checkout master
* git pull origin master
* git branch -D [YOUR_INITIALS]_[WORK_DESIGNATION]