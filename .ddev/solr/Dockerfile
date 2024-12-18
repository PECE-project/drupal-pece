#ddev-generated
FROM solr:9.6

# Fix HTTPS redirect to HTTP which breaks URL for Solr Admin UI.
# The reason for this problem is that Solr uses Jetty as a webserver.
# Jetty has X-Forwarded- headers disabled by default, enable them here:
USER root
RUN sed -i '/<!-- Uncomment to enable handling of X-Forwarded- style headers/,/-->/c\<Call name="addCustomizer"><Arg><New class="org.eclipse.jetty.server.ForwardedRequestCustomizer"/></Arg></Call>' /opt/solr/server/etc/jetty.xml
USER solr
