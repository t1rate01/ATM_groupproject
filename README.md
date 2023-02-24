# ATM PROJECT Oulu University of Applied Sciences group_2
Presented 12.12.2022

Built with MySQL, node.js / express.jsv for backend and C++/QT for frontend.

## Members:

Kolehmainen Niko, Virta Emilia, Mäki Jussi, Lampinen Roosa, **and me: Rantanen Tero**

The goal of this project was to create the front end program, rest api and database for an ATM machine.
No physical components were used in the projects (such as keypads, card readers etc).

Our group agreed right from the start that we all wanted to take part in every stage, backend and front end.
We started the project with the necessary documentary and me creating the database and its procedures.
Then we each created a raw version of the rest api, using node.js/express.js, up until to the point we had 
a login and encryption we could test with Postman/Thunder client requests. Then we each created a login part of the
frontend that communicates through the rest api. Thats when we had a checkpoint in our work and decided we need to decide
on how we would create the logic of the front end application. We spent 3 days doing individual testing and research,
after which we went with the way that is currently in the project(See UML and describing chart).
In a nutshell, different stages of the menu all consist of their own QMainWindow or QWidget class objects and their
behaviour is controlled by a class object "session" and the objects communicate using the QT's "signals and slots".

After this stage we divided the tasks based on each ones interest, available time and ability.
We divided the tasks based on the front end steps, and everyone added/edited/built the necessary 
rest api functions and routes, that took advantage of the database procedures as much as possible.

# My part in this project:

- Database and procedures  
- Rest api parts my frontend objects use  
- Front end classes: Session, login(mainwindow), Debitmainmenu, creditmainmenu, askforreceipt, receiptwindow.  

(PLEASE NOTE: According to the merge history of the project it appears almost everything was added by me.
It looks like this because all the merging/stitching before main was done in my branch, since I needed to ensure
that the updates work with my session class. Most of the time the updates were not merged in to my branch, the code
was copied from their texts to ensure working background paths in QT.)
