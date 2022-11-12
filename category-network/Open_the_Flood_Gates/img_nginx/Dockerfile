FROM nginx:latest

LABEL Author="Dylan Simmons <dylan.simmons@wustl.edu>"

# Delete default config file
RUN rm /etc/nginx/conf.d/default.conf

COPY nginx.conf /etc/nginx/nginx.conf

EXPOSE 80
