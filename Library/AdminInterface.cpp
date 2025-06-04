#include "AdminInterface.h"
#include <iostream>
#include <cstdlib>
#include "ConsoleUtils.h"

AdminInterface::AdminInterface() {
	bookManager.loadFromFile("books.json");
	authorManager.loadFromFile("authors.json");
	genreManager.loadFromFile("genres.json");
	countryManager.loadFromFile("countries.json");
	publisherManager.loadFromFile("publishers.json");
	releaseManager.loadFromFile("releases.json");
}

void AdminInterface::showEntityMenu(const std::string& entityName, IDatabaseEntity& manager) {
	int choice;
	do {
		clearScreen();
		std::cout << "\n=== " << entityName << " Menu ===\n";
		std::cout << "1. Add\n";
		std::cout << "2. Remove\n";
		std::cout << "3. Update\n";
		std::cout << "4. List All\n";

		// Extra option only for PublisherManager
		if (entityName == "Publishers") {
			std::cout << "5. List publishers without email\n";
			std::cout << "6. Count publishers\n";
			std::cout << "7. Show copies by year\n";
			std::cout << "8. Count Books Released Per Publisher\n";

		}
		else if (entityName == "Authors") {
			std::cout << "5. List authors alphabetically\n";
			std::cout << "6. Count authors per country\n";
			std::cout << "7. Show genres of author\n";
		}
		else if (entityName == "Genres")
		{
			std::cout << "5. Delete genre by name\n";
		}
		else if (entityName == "Books") {
			std::cout << "5. List books in price range\n";
			std::cout << "6. List books by author\n";
			std::cout << "7. Adjust prices by percentage\n";
		}
		else if (entityName == "Releases") {
			std::cout << "5. Book with Max Copies in Year\n";
		}

		std::cout << "0. Back\n";
		std::cout << "Choose option: ";
		std::cin >> choice;

		if (entityName == "Publishers" && choice == 5) {
			clearScreen();
			publisherManager.listPublishersWithoutEmail();
		}
		else if (entityName == "Publishers" && choice == 6) {
			clearScreen();
			publisherManager.countPublishers();
		}
		else if (entityName == "Publishers" && choice == 7) {
			std::string year;
			std::cout << "Enter release year (YYYY): ";
			std::cin >> year;
			clearScreen();
			releaseManager.countCopiesByPublisherInYear(publisherManager, year);
		}
		else if (entityName == "Publishers" && choice == 8) {
			clearScreen();
			releaseManager.countBooksPerPublisher(publisherManager);
		}

		else if (entityName == "Authors" && choice == 5) {
			clearScreen();
			authorManager.listAuthorsSortedByLastName();
		}
		else if (entityName == "Authors" && choice == 6) {
			clearScreen();
			authorManager.countAuthorsPerCountry(countryManager);
		}
		else if (entityName == "Authors" && choice == 7) {
			int authorId;
			std::cout << "Enter Author ID: ";
			std::cin >> authorId;
			clearScreen();
			bookManager.listGenresByAuthorId(authorId, genreManager, authorManager);
		}
		else if (entityName == "Genres" && choice == 5) {
			std::string name;
			std::cout << "Enter genre name to delete: ";
			std::cin.ignore();
			std::getline(std::cin, name);
			clearScreen();
			genreManager.deleteGenreByName(name);
		}
		else if (entityName == "Books" && choice == 5) {
			float minPrice, maxPrice;
			std::cout << "Enter minimum price: ";
			std::cin >> minPrice;
			std::cout << "Enter maximum price: ";
			std::cin >> maxPrice;
			clearScreen();
			bookManager.listBooksByPriceRange(minPrice, maxPrice);
		}
		else if (entityName == "Books" && choice == 6) {
			std::string lastName;
			std::cout << "Enter author's last name: ";
			std::cin.ignore();
			std::getline(std::cin, lastName);
			clearScreen();
			bookManager.listBooksByAuthorLastName(lastName, authorManager);
		}
		else if (entityName == "Books" && choice == 7) {
			float percent;
			std::cout << "Enter percentage (e.g. -12 or +15): ";
			std::cin >> percent;
			clearScreen();
			bookManager.adjustPricesByPercentage(percent);
		}
		else if (entityName == "Releases" && choice == 5) {
			std::string year;
			std::cout << "Enter year: ";
			std::cin >> year;
			releaseManager.showBookWithMaxCopiesInYear(bookManager, year);
		}


		else {
			switch (choice) {
			case 1: manager.add(); break;
			case 2: manager.remove(); break;
			case 3: manager.update(); break;
			case 4: manager.listAll(); break;
			case 0: break;
			default: std::cout << "Invalid option.\n";
			}
		}


		if (choice != 0) pause();
	} while (choice != 0);
}


void AdminInterface::run() {
	int choice;
	do {
		clearScreen();
		std::cout << "\n======= Admin Panel =======\n";
		std::cout << "1. Manage Books\n";
		std::cout << "2. Manage Authors\n";
		std::cout << "3. Manage Genres\n";
		std::cout << "4. Manage Countries\n";
		std::cout << "5. Manage Publishers\n";
		std::cout << "6. Manage Releases\n";
		std::cout << "0. Exit\n";
		std::cout << "Choose section: ";
		std::cin >> choice;

		switch (choice) {
		case 1: showEntityMenu("Books", bookManager); break;
		case 2: showEntityMenu("Authors", authorManager); break;
		case 3: showEntityMenu("Genres", genreManager); break;
		case 4: showEntityMenu("Countries", countryManager); break;
		case 5: showEntityMenu("Publishers", publisherManager); break;
		case 6: showEntityMenu("Releases", releaseManager); break;
		case 0:
			bookManager.saveToFile("books.json");
			authorManager.saveToFile("authors.json");
			genreManager.saveToFile("genres.json");
			countryManager.saveToFile("countries.json");
			publisherManager.saveToFile("publishers.json");
			releaseManager.saveToFile("releases.json");
			std::cout << "Exiting...\n";
			break;

		default: std::cout << "Invalid option.\n";
		}
	} while (choice != 0);
}
