// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

// File generated at Sun 15 Jun 2014 19:18:48

#include "genericE6SSM_input_parameters.hpp"
#include "genericE6SSM_slha_io.hpp"
#include "genericE6SSM_spectrum_generator.hpp"

#include "error.hpp"
#include "spectrum_generator_settings.hpp"
#include "lowe.h"
#include "command_line_options.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, const char* argv[])
{
   using namespace flexiblesusy;
   using namespace softsusy;
   typedef Two_scale algorithm_type;

   Command_line_options options(argc, argv);
   if (options.must_print_model_info())
      genericE6SSM_info::print(std::cout);
   if (options.must_exit())
      return options.status();

   const std::string rgflow_file(options.get_rgflow_file());
   const std::string slha_input_file(options.get_slha_input_file());
   const std::string slha_output_file(options.get_slha_output_file());
   const std::string spectrum_file(options.get_spectrum_file());
   genericE6SSM_slha_io slha_io;
   Spectrum_generator_settings spectrum_generator_settings;
   QedQcd oneset;
   genericE6SSM_input_parameters input;

   if (slha_input_file.empty()) {
      ERROR("No SLHA input file given!\n"
            "   Please provide one via the option --slha-input-file=");
      return EXIT_FAILURE;
   }

   try {
      slha_io.read_from_file(slha_input_file);
      slha_io.fill(oneset);
      slha_io.fill(input);
      slha_io.fill(spectrum_generator_settings);
   } catch (const Error& error) {
      ERROR(error.what());
      return EXIT_FAILURE;
   }

   oneset.toMz(); // run SM fermion masses to MZ

   genericE6SSM_spectrum_generator<algorithm_type> spectrum_generator;
   spectrum_generator.set_precision_goal(
      spectrum_generator_settings.get(Spectrum_generator_settings::precision));
   spectrum_generator.set_max_iterations(
      spectrum_generator_settings.get(Spectrum_generator_settings::max_iterations));
   spectrum_generator.set_calculate_sm_masses(
      spectrum_generator_settings.get(Spectrum_generator_settings::calculate_sm_masses) >= 1.0);
   spectrum_generator.set_input_scale(
      slha_io.get_input_scale());
   spectrum_generator.set_parameter_output_scale(
      slha_io.get_parameter_output_scale());
   spectrum_generator.set_pole_mass_loop_order(
      spectrum_generator_settings.get(Spectrum_generator_settings::pole_mass_loop_order));
   spectrum_generator.set_ewsb_loop_order(
      spectrum_generator_settings.get(Spectrum_generator_settings::ewsb_loop_order));
   spectrum_generator.set_beta_loop_order(
      spectrum_generator_settings.get(Spectrum_generator_settings::beta_loop_order));
   spectrum_generator.set_threshold_corrections(
      spectrum_generator_settings.get(Spectrum_generator_settings::threshold_corrections));

   spectrum_generator.run(oneset, input);

   const genericE6SSM<algorithm_type>& model
      = spectrum_generator.get_model();
   const Problems<genericE6SSM_info::NUMBER_OF_PARTICLES>& problems
      = spectrum_generator.get_problems();

   // output
   slha_io.set_spinfo(problems);
   slha_io.set_sminputs(oneset);
   slha_io.set_minpar(input);
   slha_io.set_extpar(input);
   if (!problems.have_serious_problem())
      slha_io.set_spectrum(model);

   if (slha_output_file.empty()) {
      slha_io.write_to_stream(std::cout);
   } else {
      slha_io.write_to_file(slha_output_file);
   }

   if (!spectrum_file.empty())
      spectrum_generator.write_spectrum(spectrum_file);

   if (!rgflow_file.empty())
      spectrum_generator.write_running_couplings(rgflow_file);

   const int exit_code = spectrum_generator.get_exit_code();

   return exit_code;
}
