default['dd-agent-install-script']['api_key'] = nil
default['dd-agent-install-script']['working_dir'] = '/tmp/install-script/'
default['dd-agent-install-script']['install_script_url'] = 'https://raw.githubusercontent.com/DataDog/datadog-agent/master/cmd/agent/install_script.sh'
default['dd-agent-install-script']['install_candidate'] = true

default['dd-agent-install-script']['candidate_repo_domain_apt'] = 'apt.datadoghq.com'
default['dd-agent-install-script']['candidate_repo_domain_yum'] = 'yum.datadoghq.com'
default['dd-agent-install-script']['candidate_repo_branch'] = 'testing'
