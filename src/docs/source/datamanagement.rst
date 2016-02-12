###############
Data Management
###############

This section describes the data management practical policies that were
designed for PECE. Since February 2015, the PECE design group has been working
to implement the recommendations of the Research Data Alliance's (RDA)
“Practical Policies” Working Group (WG-PP) with a focus on the needs of
empirical humanities researchers. 

----------
Definition 
----------

We designed and implemented a set of practical policies for data management per
recommendation of the RDA's WG-PP and the National Science Foundation's Data
Management Plan (DMP) of January, 18th, 2011. Qualitative research data
management in PECE encompasses four inter-related domains for human and
computer-actionable policies: preservation, disposition, privacy, and
collaboration. During the design phase, we aimed for a balance between the
necessity of preserving privacy and anonymity and the need for creating
conditions for data sharing and collaborative analysis among ethnographers,
historians, and co-participants of our projects. In practical terms, we
implemented and extended features of the Drupal framework to ensure proper data
management. This a preliminary version of our report for circulation among RDA
members to gather feedback before releasing version 1.0. 	

In sum, there are four constitutive dimensions for data management in PECE:

* **Archival:** Defining a data model is the first step for the organization of
digital ethnographic data and metadata for future storage in data repositories.
We do not aim to substitute robust, big data repository solutions with PECE but
first and foremost to help in organizing ethnographic collections for long-term
archival. In order to contribute to the task of ethnographic data preservation,
we describe data types with rich meta-data and linked data mappings (which
allows for better discoverability, replication, and, what is key for
ethnographers and historians, the capacity to ask relevant research questions
across several ethnographic collections). In practical terms, PECE offers a way
to organize, analyze, and replicate digital ethnographic collections that is
useful not only for ethnographers but for other professionals working on issues
of digital preservation of scholarly archives. We included in the PECE metadata
description important fields to account for provenance (which, in the context
of ethnographic projects, has to do with information about the project, field
sites, researchers, and methodological and theoretical orientations) in
addition to fields for contributors, licensing, shared tags, and permissions.

* **Openness:** For the purpose of data preservation, we took one step further in
organizing our data for archival, collaborative analysis, and sharing by
creating open (as in public) interfaces for data science experts to harvest
PECE Creative Commons-licensed and public domain data. We also have specified
methods for manipulating data and triggering actions on the platform according
to their status (such as the capability of deleting files when they reach their
expiration dates).

* **Privacy:** Ethnographic projects are based fundamentally on engagement between
researchers and research participants for the interpretation of sociocultural
processes. Out of the experience of engagement, a myriad of privacy and ethical
issues are potentially involved. Various types of content (from participant
observation or interviews, for instance) cannot be shared publicly due its
sensitive, and potentially privacy-infringing, information. Having the
commitment to preserve our research co-participants privacy, the PECE design
team designed the platform around the need to flag certain types of content as
private or restricted from public view. We have also specified a workflow for
helping researchers define what are the permissions that are necessary for
certain types of content, including types of data that contributors should
refrain from uploading to the platform. In addition to the PECE permission
system, we are planning to implement public-key encryption for our data store
in the next version of the platform.

* **Collaboration:** By leveraging Free and Open Source-based web technologies, open
standards, and open data with semantic extensions to support ethnographic
projects, PECE aims to help advance modes of collaborative inquiry. For this
purpose, data management involves supporting and enforcing the usage of open
formats, flexible copyright licenses, and web standards to facilitate present
and future collaborative endeavors. The PECE Design Team made the choice of
running the platform on an established web framework, Drupal, in order to
foster collaboration on many levels: Drupal's community size and geographic
distribution which spans across East Asia, Western and Eastern Europe and the
Americas; its development community constituted of companies (big and small),
local community chapters and conferences, large international conferences, as
well as numerous book publications and web resources with rich documentation
for all levels of technical skill. Several companies, community projects, and
news outlets (with big and small datasets) run on Drupal with millions of
articles, creating a vibrant community around Drupal which cooperates to
develop public, common resources by sharing code and documentation. For PECE's
sustainability in particular, this collaborative dimension is vital. We decided
to rely and contribute to upstream Drupal development and help with contributed
modules by testing, reporting, and fixing bugs. We are contributing, in
specific, a set of tools for multimedia annotation that will be of great value
for the academic community and the public.

Next, we will discuss the design and implementation of practical policies for
data management on the following topics: contextual meta-data extraction, data
control, backup, format control, retention, disposition, integrity and
replication, notification, restricted searching, instance cost reports, user
agreements (including privacy statement and users' code of conduct). In
appendix, we attached a copy of the current PECE data model and the
configuration files that were described for the practical policies.


################################ 
Practical Policy Implementations
################################

------------------------------ 
Contextual Metadata Extraction
------------------------------


