- Module: IGL
- Title: Search Engine for scientific documents
- Technology used: Django, Nextjs, Elasticsearch
- Name of the student(s): Ayyoub Kasmi, Bouchoucha Mohammed Elamine, Mougari Aymen Abderrahmane, Aoufar Fares, Arabat Ilyes
- GitHub account of the user: [Article-Search](https://github.com/Article-Search)
- [Link to the project](https://github.com/orgs/Article-Search/repositories)
- Description:
The project is mainly about extracting specific text (e.g abstract, authors) from scientific articles (as PDFs), indexing it in an ElasticSearch database, and using an SQL database to store metadata about the PDF (e.g location/URL, owner...etc). The platform involves admins adding documents to the platform, reviewers who check the auto-generated result and fix mistakes like typos, and finally anonymous who can search for documents based on several criteria (e.g upload date, author, content) where ElasticSearch is heavily involved.

The main struggle in the project for our team was with the setup and integration of Elasticsearch within our database. Among the lessons: (1) don't play smart and attempt to install ElasticSearch directly on your machine, install it within a docker image. (2) When using DRF to make your API within Django, you better setup a global handler for errors / exceptions that returns JSON instead of HTML when an error happens, because otherwise the Frontend client may crash on API calls. (3) The documentation of both Django and Python's elasticsearch package are relatively poor. AI was the solution for me mostly (MS Copilot), and it saved us in the very last moments after dealing with a horribly strange error in our package and were almost going to have nothing working XD, the problem solved at around 4:40am, with an ultimate prompt enginnering effort. (5) When using authentication that is not that complex or custom, just make use of Django's default auth's User model. (6) FastAPI might provide a better dev experience compared to Django for its simplicity, especially when it comes to small projects like this one. (7) design and divide the app from the very beginning (i.e definition of module / parts), so that collaboration can be planned as properly as possible (there's no 100% independence of all tasks, but try to delay the dependence as much as possible).

Happy hacking!

**[Go back](../../IGL.md)**
