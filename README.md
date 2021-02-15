# **Platform for Experimental and Collaborative Ethnography (PECE)**

## Table of Contents
1. [About](#about)
2. [Cite As](#cite)
3. [Contributors](#contributors)
4. [How to Access/Download/Install](#install)
5. [How to Provide Feedback](#feedback)
6. [Copyrights](#copyrights)
7. [Questions](#questions)
8. [How to Contribute](#contribute)
9. [Dependencies](#dependencies)



<div id='about'/>

## About

PECE is a Free and Open Source (Drupal-based) digital platform that supports multi-sited, cross-scale ethnographic and historical research. PECE is built as a Drupal distribution, therefore it can be extended like any other Drupal project.

This repository holds the packaged distribution for PECE adopters. It contains the most updated version of PECE for public use. If you are an end-user who wants to run PECE for your research, this is the right place to get your copy. If you are a developer wishing to contribute to the development process, you must use the [development repository](https://github.com/PECE-project/drupal-pece) instead.



<div id='cite'/>

## Cite As

Indicate how others can cite the project. If you’d like to include a DOI for the project, you can create a release of the GitHub repo and then archive the release on [Zenodo](https://zenodo.org/badge/latestdoi/52763688&sa=D&source=editors&ust=1613404827497000&usg=AOvVaw1-q5pcSIj_QObbr9FIMm-r). Zenodo will assign a DOI to the release, which you can include in the citation.

<div id='contributors'/>

## Contributors

<table>
  <tr>
    <td align="center"><a href="https://en.wikipedia.org/wiki/Michael_Scott_(The_Office)">
    <img src="https://img4.looper.com/img/gallery/the-untold-truth-of-michael-scott/l-intro-1600107071.jpg" width="100px;" alt=""/> <br />
    <b>Michael Scott</b>
    </a> <br />
    <a href="#question-kentcdodds" title="Being Annoying">💻</a>💼 </td>
      <td align="center"><a href="https://en.wikipedia.org/wiki/Jim_Halpert">
      <img src="https://img1.looper.com/img/gallery/was-jim-halpert-from-the-office-secretly-a-sociopath/intro-1565015060.jpg" width="100px;" alt=""/> <br />
      <b>Jim Halpert</b>
      </a> <br />
      <a href="#question-kentcdodds" title="Being Annoying">📋</a> </td>   

  </tr>
  <tr>

</table>


<div id='install'/>

## How to Access/Download/Install


### How do I install PECE?
PECE is a Free Software-based Drupal distribution, therefore the standard installation procedure for Drupal 7 applies to PECE with a few extra dependencies.

The following instructions have been tested on a Debian 8 (jessie) server, but they are not OS-dependent. PECE should run on any system supported by Drupal 7. PECE has been tested in virtual machines with 256M allocated for PHP, being 128M the recommended minimum for Drupal 7 distributions. Your configuration, of course, may vary considerably depending on the usage you are making of the platform. Refer to our data management guidelines under the "sustainability" section to learn about the recommended minimum specs for your servers.


### Downloading the Distro
Our distribution is currently being developed on Github. You can obtain the most updated version following the link "Releases" on the project's git repository:

```
https://github.com/PECE-project/pece-distro
```

Alternatively, you can obtain the source code and build the distro yourself if you intend to help our team by fixing bugs and extending the platform for your research purposes:

```
git clone https://github.com/PECE-project/drupal-pece.git
```
If you are a developer who wants to contribute to PECE, you will need to follow special instructions to install and configure the tools for building the distro. Consult the sub-section Setting up the Development Environment below for more information.


### Quick Install
If you have the server backend already set-up, you can quickly install PECE following these steps:

### Clone the ''pece-distro'' repository:

```
git clone https://github.com/PECE-project/pece-distro.git
```

### Create an empty database:

```
mysql -u $YOUR_USER -p -e "CREATE DATABASE $YOUR_DB_NAME CHARACTER SET utf8 COLLATE utf8_general_ci;"
```

Proceed to the URL in which your Drupal will reside, i.e. https://worldpece.org. From there, you can install PECE like any other Drupal site. Follow the Drupal.org official documentation if you need further help. In the section Troubleshooting below we describe common issues users have when trying to install PECE without the proper backend dependencies, configurations, and permissions.

One important note: please, make sure to set the permissions on the filesystem properly. We cannot emphasize this enough. The official Drupal documentation explains how to do so, if you have questions. (In our experience, we have needed to set the file permissions at sites/default/files/artifacts to 770 and sites/default/files/private to 770.)



<div id='feedback'/>

## How to Provide Feedback

To report an issue, head on over to https://github.com/PECE-project/pece-distro/issues and create an issue there.



<div id='copyrights'/>

## Copyrights



<div id='questions'/>

## Questions

For any inquiries, send an email to pece.tech.team@gmail.com



<div id='contribute1'/>

## How to Contribute

There are many ways of contributing to the PECE project. One of them is by reporting bugs or requesting features through Github in our [development repository](https://github.com/PECE-project/drupal-pece). Read our [contributors' guide](http://pece.readthedocs.io/en/latest/contributors.html) for more information about how to contribute code and bug fixes.

Bug and feature requests for this project are documented in this repo’s [issues queue](https://github.com/PECE-project/pece-distro/issues). You can contribute to the project by writing code to fix issues or to create new features. When contributing code, please be sure to:
- Fork this repository.
- Modify the code (changing only one thing at a time), and then issue a pull request for each change.
- Follow the project's coding style (using K&R-style indentation and bracketing, commenting above each feature, and using snake case for variables). [Feel free to swap out with specific conventions]
- Test your code locally before issuing a pull request.
- Clearly state the purpose of your change in the description field for each commit.




<div id='dependencies'/>

## Dependencies

In addition to the [basic Drupal system requirements](https://www.drupal.org/requirements), you will need these extra libraries:

- php5-mcrypt
- php5-curl
- php-ssh2
- pecl-yaml (for YAML parsing)

Even though these are not hard dependencies, we highly recommend running your PECE site with following set-up for better security and performance:

- nginx
- php (>= 5.5)
- php5-fpm
- drush (>= 5.x)
- any *nix OS of your choice
- cURL
