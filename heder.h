#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<stdio.h>

// UI Functions
void separator();
void doubleline();

// Registration Functions
void voter_registration();
void candidate_registration();
int Party_Registration();
int loging_party();

// Login Functions
void voter_login();
void voter_logout();
int is_voter_logged_in();

void candidate_login();
void candidate_logout();
int is_candidate_logged_in();

void party_login();
void party_logout();
int is_party_logged_in();

void voter_login();
void voter_logout();
int is_voter_logged_in();

// Admin Functions
void admin_panel();
void admin_set_polling_time();
int is_admin_logged_in();
int is_polling_active();

// Polling Functions
void polling();
int has_voter_voted(char *nic);


// Results Functions
void results();
void display_overall_results();
void display_resultsgit_by_district();
void display_results_by_party();
void view_candidate_performance(char *candidate_name);
void candidate_view_results(char *candidate_name);

#endif