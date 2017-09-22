# Git Node
* Git-Node
** Initializing
   echo "# Initialize readme.org" >> README.org
   git init
   git add README.md

** Checking the status
   git status
   /// ignore something
   git status -uno
   // git status --untracked-files=no
** Adding changes
   git add test.txt
   git add .
   git add '*.txt'

** Committing
   git commit -m "Add the message"

** History checking
   git log

** Remote respositories
   git remote add origin https://github.com/try-git/try_git.git
** Pushing
   git push
   
   //pushing remote
   git push -u origin master

   -u for remember the parameters

** Differences
   git diff HEAD

   git add octofamily/octodog.txt

   git diff --staged

   git reset octofamily/octodog.txt

   git checkout -- octocat.txt

** Braching out
   git branch clean_up

   git checkout clean_up

** Removing the things
   git rm file1.txt
   git rm '*.txt'
   But if you want to remove the file only from the Git repository and not remove it from the filesystem, use:

   git rm --cached file1.txt
   and add changes 
   git push origin branch_name
** Switching
   git checkout master

** Merge
   git merge clean_up

** delete brach
   git branch -d clean_up
   

