Git PHP Deploy
==============

PHP WebHOOK for pulling a repository upon a commit.


Why?
----

To automatically update a staging server when a new commit is made.

Status
------

Untested

How?
----

 1. Clone your target repostiry in directory x.

 2. Create a config.ini with sections for each local repository to pull set the path variable to x.

    [myrepox]
    
    path = x

 3. Setup a webserver on which the hook is server. I recommend restricting the allowed remote IPs to those used by GitHub.

 4. Go to your repository settings on GitHub and add the URL to your hosted deploy.php.


Further reading
-----------------

 * https://help.github.com/articles/post-receive-hooks
