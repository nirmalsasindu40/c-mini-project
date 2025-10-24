#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

// UI Functions
void separator();
void doubleline();

// Registration Functions
void voter_registration();
void candidate_registration();
int Party_Registration();

// Login Functions
int loging_party();
void voter_login();
void voter_logout();
int is_voter_logged_in();

void candidate_login();
void candidate_logout();
int is_candidate_logged_in();

// Admin Functions
void admin_panel();
void admin_login();
void admin_set_polling_time();
void start_polling();
void stop_polling();
int is_admin_logged_in();
int is_polling_active();

// Polling Functions
void polling();
int has_voter_voted(char *nic);
int verify_voter(char *username, char *password, char *voter_nic, char *voter_district);
void display_candidates(char *voter_district);
int verify_candidate_in_district(char *candidate_name, char *voter_district);
void record_vote(char *candidate_name, char *voter_nic, char *voter_district);
void mark_voter_as_voted(char *nic);
void to_lowercase(char *str, char *result);

// Results Functions
void results();
void display_overall_results();
void display_results_by_district();
void display_results_by_party();
void view_candidate_performance();
void candidate_view_results();
int count_total_votes();
int count_votes_for_candidate(char *candidate_name);

#endif