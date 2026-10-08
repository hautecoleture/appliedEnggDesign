# `git` Reference 

`git` is a version control system that allows people to collaborate on a project together while preserving changes made. It allows people to work on the same code base without overwriting changes others have made in real time. 

GitHub is the website that hosts a shared copy of this repository. `git` runs on your computer; GitHub is where everyone's work meets.

**NOTE:** I have used Claude to help write this out. I have spot-checked it and it appears to be correct on the first pass. If you have any questions, both Gemini and Claude are useful here, although they tend to overcomplicate things. Feel free to send me a message if you are unsure; I promise you cannot break anything -- Jon. 
## Key Terms

| Term | Meaning |
| --- | --- |
| **Repository (repo)** | The project folder, plus its full history of changes. |
| **Commit** | A saved snapshot of the project with a short message describing what changed. |
| **Branch** | A separate line of work. Lets you change things without touching `master` until you're ready. |
| **Remote (`origin`)** | The copy of the repo on GitHub. |
| **Push / Pull** | Send your commits to GitHub / bring others' commits down from GitHub. |
| **Merge** | Combine the changes from one branch into another. |

## One-Time Setup

Install `git` ([git-scm.com](https://git-scm.com/downloads)), then tell it who you are:

```
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
```

## Getting the repository from GitHub

Use the following code:

```
git clone https://github.com/hautecoleture/appliedEnggDesign.git
cd appliedEnggDesign
```

This only needs to be done once. It creates a folder with the project inside.

## The Everyday Workflow

### 1. Get the latest changes before you start

```
git pull
```

### 2. Make a branch for your work

```
git switch -c <branch-name>
```

Use a short descriptive name, e.g. `servo` or `pwmControl`. To move to a branch that already exists, drop the `-c`:

```
git switch <branch-name>
```

### 3. Edit files, then check what changed

```
git status        # which files changed
git diff          # the exact lines that changed
```

### 4. Stage and commit

Staging picks which changes go into the next snapshot:

```
git add <file>    # stage one file
git add .         # stage everything in the current folder
```

Then save the snapshot with a message:

```
git commit -m "Short description of what you changed"
```

Commit often, in small pieces that each do one thing.

### 5. Push your branch to GitHub

The first time you push a new branch:

```
git push -u origin <branch-name>
```

After that, just:

```
git push
```

### 6. Merge into `master` when the work is done

```
git switch master
git pull
git merge <branch-name>
git push
```

Alternatively, open a **Pull Request** on GitHub, so a teammate can review before merging.

**NOTE:** I should have GitHub configured to where it does a pull request regardless. 

## Handy Commands

```
git branch            # list branches (* marks the one you're on)
git log --oneline     # list past commits
git restore <file>    # throw away uncommitted changes to a file (cannot be undone)
```

## Merge Conflicts

If two people changed the same lines, `git` will stop and mark the file like this:

```
<<<<<<< HEAD
your version
=======
their version
>>>>>>> other-branch
```

Edit the file to keep what you want, delete the marker lines, then:

```
git add <file>
git commit
```

## Tips

- Run `git status` whenever you're unsure what state you're in.
- Always `git pull` before starting work.
- Don't work directly on `master`; use a branch.
    - *I did not always follow this tip, for what its worth*
- I would recommend creating your own branch the following way
    ``` 
    git branch <BRANCH_NAME>
    git checkout <BRANCH_NAME>
    ```
