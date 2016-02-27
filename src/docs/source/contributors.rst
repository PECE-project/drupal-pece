##################
Contributors Guide
##################

Statement on Free and Open Source Software, Open Data, and Open Access
----------------------------------------------------------------------

PECE has incorporated developers from all around the Open Source world to
ensure that PECE does Free and Open Source right: having code licensed properly
is a good start but insufficient, a community around the software and a proper
spirit of openness is what is needed. A fundamental goal of PECE is to bring
the Open Source and humanities communities together on equal footing and mutual
respect for differences. In that regard, we hope PECE is as interesting and
successful as an Open Source project in its own right as it is a platform for
social scientists. We are committed to all contributions, large and small. PECE
works best as an experimental space for technical and non-technical people
alike. As our technical and non-technical communities grow, we envision the
collaboration between the two leading to greater insights from all. PECE is
dedicated to the long-term.

PECE relies upon open web standards to guarantee interoperability and avoid
vendor lock-ins and Open Data to encourage and create infrastructural
conditions to promote data sharing in contexts of little to almost nonexistent
collaboration among research groups --- and, last but not least, Open Access to
advance the goals of returning public funded research to the public. In
practical terms, PECE applies these concepts by:

* Enforcing the usage of open data and open document formats (such as open, web
  safe formats for multimedia files; open formats for documents such as the
  ODF, and established web standards such as JSON, XML, and RDF for data
  exchange and relationality);

* Providing technical conditions for data sharing by enforcing the usage of
  flexible copyright licenses, such as Creative Commons suite, when applicable
  for ethnographic data;

* Contributing code directly to Drupal projects, instead of forking code and
  working locally and not sharing bug fixes and improvements with the larger
  user and developer community;

* Participating and actively contributing to Free and Open Source projects as
  well as initiatives for Open Access in anthropology and STS, therefore
  bridging the Free and Open Source community efforts with academic disciplines
  and transdisciplinary contexts;

* Drawing from the orientation of the Open Data community regarding
  best-practices for data sharing and open inter-exchange formats; Following
  the community work for debating and creating "codes of conduct"

Guidelines for New Contributors
-------------------------------

At this point, PECE is much more advanced and sophisticated in its theoretical
underpinnings and specification, rather than in its actual implementation.
The implentation follows from the general orientation of our design logics and
our of the necessity of specific "substantive logics". So it is a good idea 
for any new contributor to pay attention to the verbose theoretical parts to
understand what the platform wants to accomplish with the same attention one
would pay to the data model, the APIs we use, and other technical specifications.

Mark Seemann has an interesting `post <http://blog.ploeh.dk/2015/01/15/10-tips-for-better-pull-requests>`_ on 
how to better organize "pull requests". In the same spirit, we welcome pull requests
that:

* Are kept small, doing one and only one thing

* Do not change the syntax style, which follows  the Drupal community

* Lines are kept below 80 columns for readability

* Are tested and made sure it is ready for merging with a clean commit history

* Clearly explain what you trying to accomplish and why you are contributing a change

In terms of attribution, all the contributors are recognized in the AUTHORS file and
in the section "Team" of this document. For managing the legal aspects of the project,
we have an non-profit education NGO, described in the legal section, which is listed
as the copyright holders **for the purposes of its inversion copylefting all
we do**).


Submitting your Contribution
----------------------------

When submitting your contribution, it is good form to stick to a basic template
which has been developed by the Drupal community to communicate issues and requested
changes:

* What is the motivation for this request? 

* What solution do you propose?

* Are there remaining tasks? What are they?

* What part of the platform is impacted? API, data model, UI, etc.?

* Describe the "acceptance criteria" in the comments of your pull request

For further information, please `read the official Drupal documentation 
<https://www.drupal.org/node/1155816>`_ on how to report an issue
to the development team.
