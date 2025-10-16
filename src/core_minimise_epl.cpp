# include <iostream>
// # include <armadillo>
# include <RcppArmadillo.h>
# include "core_sample_of_partitions.h"
# include "core_variation_of_information.h"
# include "core_binder.h"
# include "core_normalised_variation_of_information.h"
# include "core_normalised_information_distance.h"

// the function randomShuffle is just a utils to shuffle an arma::vec
arma::vec randomShuffle(arma::vec a) {
  Rcpp::IntegerVector b = Rcpp::sample(a.n_elem, a.n_elem);
  arma::vec res(a.n_elem);
  for (unsigned int index=0; index<a.n_elem; ++index) {
    res.at(index) = b.at(index) - 1;
  }
  return res;
}

template< class T >
arma::vec MinimiseEpl (T * data, unsigned int max_n_iter) {
  // std::cout << "\n\nExpected Posterior " << data->loss_function_name << " loss minimisation starting ..." << std::endl;
  unsigned int iter, index, i;
  arma::wall_clock timer;
  double tempo;
  bool stop_condition;
  unsigned int h_best;
  arma::uword h_best_uword;
  double delta_best;
  arma::vec pool = arma::linspace<arma::vec>(0, data->N-1, data->N);
  arma::vec epl_store;
  
  epl_store.set_size(max_n_iter*data->N+1);
  epl_store.at(0) = data->epl_value;
  stop_condition = false;
  iter = 0;
  timer.tic();
  while (!stop_condition && iter < max_n_iter)
  {
    pool = randomShuffle(pool);
    for (index=0; index<data->N; ++index)
    {
      i = pool.at(index);
      data->EvaluateDeltas(i);
      h_best_uword = data->deltas.index_min();
      delta_best = data->deltas.at(h_best_uword);
      h_best = h_best_uword;
      if (delta_best < 0) data->Move(i,h_best);
      epl_store.at(1+data->N*iter+index) = data->epl_value;
    }// end of iteration
    index = 0;
    ++iter;
    if (iter > 0) if (data->epl_value >= epl_store.at(1+data->N*(iter-1)) - 0.00001) stop_condition = true;// 0.00001 is a tolerance parameter
  }// end of optimisation
  epl_store = epl_store.subvec(0,data->N*iter+index);
  tempo = timer.toc(); 
  // std::cout << "\n... Expected Posterior " << data->loss_function_name << " loss minimisation finished in " << tempo << " seconds\n\n" << std::endl;
  return (epl_store);
}


// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

Rcpp::List p__MinimiseAverageVI (arma::mat sample_of_partitions, arma::vec weights, arma::vec decision_init) {
  variation_of_information data(sample_of_partitions,weights,decision_init);
  arma::vec epl_store;
  epl_store = MinimiseEpl(&data, 100);
  return (Rcpp::List::create(Rcpp::Named("EPL_stored_values") = epl_store, Rcpp::Named("EPL") = data.epl_value, Rcpp::Named("decision") = data.decision));
}

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

Rcpp::List p__MinimiseAverageB (arma::mat sample_of_partitions, arma::vec weights, arma::vec decision_init) {
  binder data(sample_of_partitions,weights,decision_init);
  arma::vec epl_store;
  epl_store = MinimiseEpl(&data, 100);
  return (Rcpp::List::create(Rcpp::Named("EPL_stored_values") = epl_store, Rcpp::Named("EPL") = data.epl_value, Rcpp::Named("decision") = data.decision));
}

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

Rcpp::List p__MinimiseAverageNVI (arma::mat sample_of_partitions, arma::vec weights, arma::vec decision_init) {
  normalised_variation_of_information data(sample_of_partitions,weights,decision_init);
  arma::vec epl_store;
  epl_store = MinimiseEpl(&data, 100);
  return (Rcpp::List::create(Rcpp::Named("EPL_stored_values") = epl_store, Rcpp::Named("EPL") = data.epl_value, Rcpp::Named("decision") = data.decision));
}

// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]

Rcpp::List p__MinimiseAverageNID (arma::mat sample_of_partitions, arma::vec weights, arma::vec decision_init) {
  normalised_information_distance data(sample_of_partitions,weights,decision_init);
  arma::vec epl_store;
  epl_store = MinimiseEpl(&data, 100);
  return (Rcpp::List::create(Rcpp::Named("EPL_stored_values") = epl_store, Rcpp::Named("EPL") = data.epl_value, Rcpp::Named("decision") = data.decision));
}

