#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> split(const std::string& str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while (stop != std::string::npos)
	{
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

std::vector<int> transform(std::vector<std::string>& s) {
	std::vector<int> sint;
	for (auto ip = s.cbegin(); ip != s.cend(); ++ip)
	{
		sint.push_back(std::stoi(*ip));
	}
	return sint;
}

int main()
{
	try
	{
		std::vector<std::vector<std::string> > ip_pool;

		for (std::string line; std::getline(std::cin, line);)
		{
			std::vector<std::string> v = split(line, '\t');
			ip_pool.push_back(split(v.at(0), '.'));
		}

		std::sort(ip_pool.rbegin(), ip_pool.rend(), [](std::vector<std::string>& l, std::vector<std::string>& r) {
			std::vector<int> lint, rint;
			lint = transform(l);
			rint = transform(r);
			return std::lexicographical_compare(lint.cbegin(), lint.cend(), rint.cbegin(), rint.cend()); });

		for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
		{
			for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
			{
				if (ip_part != ip->cbegin())
				{
					std::cout << ".";

				}
				std::cout << *ip_part;
			}
			std::cout << std::endl;
		}

		// TODO filter by first byte and output
		auto filterfb = [](int&& i, auto ip_pool) {
			for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
			{
				auto ip_cbegin = ip->cbegin();
				if (*ip_cbegin == std::to_string(i))
				{
					for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
					{
						if (ip_part != ip->cbegin())
						{
							std::cout << ".";

						}
						std::cout << *ip_part;
					}
					std::cout << std::endl;
				}
			}
			};
		filterfb(1, ip_pool);

		// TODO filter by first and second bytes and output
		auto filterfsb = [](int&& i, int&& j, auto ip_pool) {
			for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
			{
				auto ip_cbegin = ip->cbegin();
				auto next = ip_cbegin;
				next++;
				if (*ip_cbegin == std::to_string(i) && *next == std::to_string(j))
				{
					for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
					{
						if (ip_part != ip->cbegin())
						{
							std::cout << ".";

						}
						std::cout << *ip_part;
					}
					std::cout << std::endl;
				}
			}
			};
		filterfsb(46, 70, ip_pool);

		// TODO filter by any byte and output
		auto filter_any = [](int&& i, auto ip_pool) {
			for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
			{
				if (std::find(ip->cbegin(), ip->cend(), std::to_string(i)) != ip->cend())
				{
					for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
					{
						if (ip_part != ip->cbegin())
						{
							std::cout << ".";

						}
						std::cout << *ip_part;
					}
					std::cout << std::endl;
				}
			}
			};
		filter_any(46, ip_pool);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
