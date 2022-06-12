CC=gcc
CFLAGS= -g

SRC := ./src/
TMP := ./tmp/
DST := ../cakes/


$(DST)beginner_cake $(DST)intermediate_cake $(DST)expert_box $(DST)expert_chocolate $(DST)expert_cheese $(DST)expert_crab $(DST)expert_pineapple &: $(TMP)box $(TMP)cheese $(TMP)chocolate $(TMP)crab $(TMP)pineapple $(TMP)cookie $(TMP)beginner $(DST).gitignore
	python3 ./alter_recipes.py

$(DST).gitignore:
	mkdir -p $(DST)
	touch $(DST).gitignore
	echo "*" > $(DST).gitignore

$(TMP).gitignore:
	mkdir -p $(TMP)
	touch $(TMP).gitignore
	echo "*" > $(TMP).gitignore


$(TMP)box: $(SRC)recipe_box_cake.c $(TMP).gitignore
	$(CC) -o $(TMP)box $(SRC)recipe_box_cake.c 

$(TMP)cheese: $(SRC)recipe_cheesecake.c $(TMP).gitignore
	$(CC) -o $(TMP)cheese $(SRC)recipe_cheesecake.c 

$(TMP)chocolate: $(SRC)recipe_chocolate_cake.c $(TMP).gitignore
	$(CC) -o $(TMP)chocolate $(SRC)recipe_chocolate_cake.c 

$(TMP)crab: $(SRC)recipe_crabcake.c $(TMP).gitignore
	$(CC) -o $(TMP)crab $(SRC)recipe_crabcake.c

$(TMP)pineapple: $(SRC)recipe_pineapple_cake.c $(TMP).gitignore
	$(CC) -o $(TMP)pineapple $(SRC)recipe_pineapple_cake.c

$(TMP)cookie: $(SRC)recipe_cookie_cake.c $(TMP).gitignore
	$(CC) -o $(TMP)cookie $(SRC)recipe_cookie_cake.c

$(TMP)beginner: $(SRC)recipe_beginner.c $(TMP).gitignore
	$(CC) -o $(TMP)beginner $(SRC)recipe_beginner.c

clean:
	rm -rf $(TMP)
	rm -rf $(DST)
